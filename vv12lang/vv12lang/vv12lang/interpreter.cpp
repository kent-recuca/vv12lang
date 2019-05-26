#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include "util.h"
#include "proc.h"
using namespace std;

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  ルートクラス
	//--------------------------------------------------------------------------------------
	struct Root::Impl {
		const StatementList* m_StatementList;
	};

	Root::Root(const StatementList* stml) :
		StmExBase(ObjType::RootType),
		pImpl(new Impl)
	{
		pImpl->m_StatementList = stml;
	}

	Root::~Root() {
		delete pImpl;
	}

	const StatementList* Root::getStmeList()const {
		return pImpl->m_StatementList;
	}

	SmtRes Root::Excute()const {
		setRuntimeLineNumber();
		if (pImpl->m_StatementList) {
			auto pos = pImpl->m_StatementList;
			do {
				auto stm = pos->getStm();
				stm->Excute();
				pos = pos->getNext();
			} while (pos);
		}
		else {
			Interpreter::getInp()->runtimeExit(2001);
		}
		return SmtRes();
	}

	//--------------------------------------------------------------------------------------
	///  ランタイムオブジェクト
	//--------------------------------------------------------------------------------------
	struct RuntimeObject : public std::enable_shared_from_this<RuntimeObject> {
		bool m_IsFunc;
		//変数のmap
		map<string, Value> m_VariableMap;
		//ツリー構造
		weak_ptr<RuntimeObject> m_Parent;
		shared_ptr<RuntimeObject> m_Child;
		RuntimeObject(shared_ptr<RuntimeObject> parent, bool IsFunc = false) :
			m_Parent(parent), m_Child(nullptr), m_IsFunc(IsFunc)
		{}
		~RuntimeObject() {}
	};

	//--------------------------------------------------------------------------------------
	///  インタープリタクラス
	//--------------------------------------------------------------------------------------
	Interpreter* Interpreter::getInp() {
		static Interpreter* instance = nullptr;
		if (!instance) {
			instance = new Interpreter;
		}
		return instance;
	}

	struct Interpreter::Impl {
		set<string> m_FixedStringPool;
		vector<ObjBase*> m_ObjectPool;
		map<string, string> m_ConfigMap;
		//文字列リテラル作成用
		string m_LiteralTemp;
		//ランタイムエラー用テンポラリ
		Value m_TempVal;
		Root* m_Root;
		shared_ptr<RuntimeObject> m_CurrentRuntime;
		shared_ptr<RuntimeObject> m_RootRuntime;
		//エラーのマップ
		map<int, string> m_ErrMap;
		//警告を表示するかどうか
		bool m_IsWorningOut;
		//ランタイム中の行番号
		int m_RuntimeLineNumber;
		//breakの深さ
		int m_BreakDeps;
		//Loopの深さ
		int m_LoopDeps;

	};

	Interpreter::Interpreter() :
		ObjBase(ObjType::InterpreterType),
		pImpl(new Impl)
	{
		pImpl->m_Root = nullptr;
		pImpl->m_ErrMap =
		{
			{ 0001, "を確認すべきである。" },
			{ 0002, "その手前では一時停止しなくてはならない。" },
			{ 1001, "ファイルのなめえ（名前）が指定されてないぞい。" },
			{ 1002, "ファイルを読むのに失敗したぞい。" },
			{ 1003, "書ぎがだがまじがってんぞい。" },
			{ 1004, "関数名はすでにつかわれでっつおい。"},
			{ 1005, "関数が見づがんねぞい。ない関数を呼んだってだめだべ。よぶどごより上で作ってくんつえ。"},
			{ 2001, "実行文がねがら動がせねぞい。" },
			{ 2002, "なんだがわがんねエラーだぞい" },
			{ 2003, "0では割れねぞい。" },
			{ 2004, "演算でぎねぞい"},
			{ 2005, "右辺が負の数だと文字列の掛け算はでぎねぞい。正の数字ならでぎっつおい。" },
			{ 2006, "左辺が文字列だと引き算でぎねぞい。足し算か掛け算ならでぎっつおい。" },
			{ 2007, "左辺が文字列だと割り算でぎねぞい。足し算か掛け算ならでぎっつおい。" },
			{ 2008, "bool型はほかの型とは比較でぎねぞい。bool同士ならでぎっつおい。" },
			{ 2009, "文字列は比較でぎねぞい" },
			{ 2010, "比較演算がでぎねぞい"},
			{ 2011, "ローカル変数は関数のながでしがつぐれねぞい。"},
			{ 2012, "定義関数で、キーが空白でねえがい？"},
			{ 2013, "関数呼び出しで、パラメータ数より実引数が多いぞい。関数定義をよぐみでくんつえ。"},
			{ 2014, "関数のながに関数をづぐろうどしてんべ。すまねが、それはでぎんよ。"},
			{ 2015, "なんだがわがんねげど、ループがスイッチが開いてねえが閉じてねえどごがあんぞい。"},
			{ 2016, "ブレーク文はループの中がスイッチのながしかかげねぞい。"},
			{ 2017, "リターン文は関数内でしかかげねぞい。"},
			{ 2018, "コンティニュー文はループの中しかかげねぞい。"},
			{ 2019, "配列の添え字は正の整数か文字列だぞい"},
			{ 2020, "親配列がないぞい"},
			{ 2021, "配列はほがの型に変換でぎねぞい。"},
			{ 2022, "その配列の添え字はめっかんねぞい。"},
		};

		//初期状態はワーニングを出す
		pImpl->m_IsWorningOut = true;
		pImpl->m_RuntimeLineNumber = 1;
		pImpl->m_TempVal = Value();
		pImpl->m_ConfigMap["calc_epsilon"] = "0.000001";
	}
	Interpreter::~Interpreter() {
		delete pImpl;
	}

	int Interpreter::Compile(FILE *fp) {
		extern int yyparse(void);
		extern FILE* yyin;
		yyin = fp;
		if (yyparse()) {
			return 1;
		}
		return 0;
	}

	void Interpreter::Exec()const {
		if (pImpl->m_Root) {
			pImpl->m_CurrentRuntime = make_shared<RuntimeObject>(nullptr);
			pImpl->m_RootRuntime = make_shared<RuntimeObject>(nullptr);
			pImpl->m_Root->Excute();
		}
		else {
			Interpreter::getInp()->runtimeExit(2001);
		}
	}

	///１階層ランタイムをpushする
	void Interpreter::pushRuntime(bool IsFunc) {
		pImpl->m_CurrentRuntime->m_Child = make_shared<RuntimeObject>(pImpl->m_CurrentRuntime, IsFunc);
		pImpl->m_CurrentRuntime = pImpl->m_CurrentRuntime->m_Child;
	}
	///１階層ランタイムをpopする
	void Interpreter::popRuntime() {
		auto parPtr = pImpl->m_CurrentRuntime->m_Parent.lock();
		if (parPtr) {
			pImpl->m_CurrentRuntime = parPtr;
			pImpl->m_CurrentRuntime->m_Child.reset();
		}
	}

	//ループ実行中かどうか
	void Interpreter::pushLoop() {
		pImpl->m_LoopDeps++;

	}
	void Interpreter::popLoop() {
		pImpl->m_LoopDeps--;
		if (pImpl->m_LoopDeps < 0) {
			Interpreter::getInp()->runtimeExit(2015);
		}
	}

	void Interpreter::pushBreak() {
		pImpl->m_BreakDeps++;

	}

	void Interpreter::popBreak() {
		pImpl->m_BreakDeps--;
		if (pImpl->m_BreakDeps < 0) {
			Interpreter::getInp()->runtimeExit(2015);
		}
	}



	void Interpreter::Delete() {
		for (auto v : pImpl->m_ObjectPool) {
			delete v;
		}
		pImpl->m_ObjectPool.clear();
		pImpl->m_FixedStringPool.clear();
	}

	void Interpreter::setConfig(const char* key, const Value val) {
		//congigファイルは文字列
		string keystr = key;
		string valstr = val.getString();
		if (keystr == "") {
			runtimeExit(2012);
		}
		pImpl->m_ConfigMap[keystr] = valstr;
	}

	Value Interpreter::getConfig(const char* key) {
		//congigファイルは文字列
		string keystr = key;
		if (keystr == "") {
			runtimeExit(2012);
		}
		return Value(pImpl->m_ConfigMap[keystr].c_str());
	}

	void Interpreter::pushBackObject(ObjBase* pobj) {
		pImpl->m_ObjectPool.push_back(pobj);
	}

	const char* Interpreter::createFixedString(const char* ext) {
		//255文字に切り詰める。
		auto str = clampToken(ext);
		auto it = pImpl->m_FixedStringPool.insert(str);
		return it.first->c_str();
	}

	Expression* Interpreter::createVariableExp(const char* ident) {
		string str = clampToken(ident);
		auto ptr = new VariableExp(str.c_str());
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	Expression* Interpreter::createIntLiteralExp(const char* ext) {
		string str = clampToken(ext);
		auto ptr = new IntLiteralExp(std::stoi(str));
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	Expression* Interpreter::createDoubleLiteralExp(const char* ext) {
		string str = clampToken(ext);
		auto ptr = new DoubleLiteralExp(std::stod(str));
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	Expression* Interpreter::createBinaryExp(const Expression* left, const Expression* right, ExpressionType t) {
		auto ptr = new BinaryExp(t, left, right);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	Expression* Interpreter::createAssExp(const Expression* ident, const Expression* right) {
		auto ptr = new AssignExp(ident, right);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	Expression* Interpreter::createToAssExp(const Expression* ident, const Expression* right, ExpressionType t) {
		auto ptr = new ToAssExp(ident, right, t);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	void Interpreter::startStringLiteral() {
		pImpl->m_LiteralTemp = "";
	}

	void Interpreter::addStringLiteral(char ext) {
		pImpl->m_LiteralTemp += ext;
	}

	Expression* Interpreter::createStringLiteralExp() {
		auto ptr = new StringLiteralExp(pImpl->m_LiteralTemp.c_str());
		pImpl->m_LiteralTemp = "";
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	StatementList* Interpreter::createStatementList(const Statement* stm) {
		auto ptr = new StatementList(stm);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	StatementList* Interpreter::createStatementList(StatementList* stml, const Statement* stm) {
		StatementList *pos;
		if (stml == nullptr)
			return createStatementList(stm);
		for (pos = stml; pos->getNext(); pos = pos->getNext())
			;
		pos->setNext(createStatementList(stm));
		return stml;
	}

	Root*  Interpreter::createRoot(const StatementList* stml) {
		auto ptr = new Root(stml);
		pImpl->m_ObjectPool.push_back(ptr);
		//インタプリタのrootにセット
		pImpl->m_Root = ptr;
		return ptr;
	}

	///変数の値を取得
	Value& Interpreter::getGlobalValiableValue(const char* key) {
		//ルートの変数（グローバル変数）を得る
		auto it = pImpl->m_RootRuntime->m_VariableMap.find(key);
		if (it != pImpl->m_RootRuntime->m_VariableMap.end()) {
			//見つかった
			return it->second;
		}
		else {
			//無かったので作成
			//stringで作成
			pImpl->m_RootRuntime->m_VariableMap[key] = Value("");
			return pImpl->m_RootRuntime->m_VariableMap[key];
		}
	}

	void Interpreter::setRuntimeLineNumber(int num) {
		pImpl->m_RuntimeLineNumber = num;

	}
	int Interpreter::getRuntimeLineNumber() const {
		return pImpl->m_RuntimeLineNumber;
	}

	void Interpreter::syntaxKeepExit(int mess_id, const char* detail) {
		cerr << "\n"
			<< pImpl->m_ErrMap[1003]
			<< detail
			<< ": "
			<< pImpl->m_ErrMap[mess_id]
			<< endl;
		exit(1);
	}


	void Interpreter::syntaxExit(int mess_id, int linnum, const char* detail, bool bison) {
		string detailstr = detail;
		if (bison) {
			if (detailstr != "") {
				cerr << "\n"
					<< pImpl->m_ErrMap[mess_id]
					<< linnum
					<< " 行目: "
					<< detailstr
					<< " 付近"
					<< pImpl->m_ErrMap[0001]
					<< pImpl->m_ErrMap[0002]
					<< endl;
			}
			else {
				cerr << "\n"
					<< pImpl->m_ErrMap[mess_id]
					<< linnum
					<< " 行目付近"
					<< pImpl->m_ErrMap[0001]
					<< endl;

			}
		}
		else {
			if (detailstr != "") {
				cerr << "\n"
					<< pImpl->m_ErrMap[mess_id]
					<< linnum
					<< " 行目: "
					<< detailstr
					<< " 付近"
					<< pImpl->m_ErrMap[0001]
					<< pImpl->m_ErrMap[0002]
					<< endl;
			}
			else {
				cerr << "\n"
					<< pImpl->m_ErrMap[mess_id]
					<< linnum
					<< " 行目付近"
					<< pImpl->m_ErrMap[0001]
					<< endl;
			}
		}
		exit(1);
	}

	void Interpreter::runtimeExit(int mess_id, const char* target) {
		if (target) {
			cerr << "\nクリープ現象時の注意点である。 "
				<< getRuntimeLineNumber()
				<< " 行目: "
				<< target
				<< " "
				<< pImpl->m_ErrMap[mess_id]
				<< endl;

		}
		else {
			cerr << "\nクリープ現象時の注意点である。 "
				<< getRuntimeLineNumber()
				<< " 行目: "
				<< pImpl->m_ErrMap[mess_id]
				<< endl;

		}
		exit(1);
	}

	void Interpreter::runtimeWorning(int mess_id) {
		if (isWorningOut()) {
			cerr << "\nクリープ現象時の注意点である。左右確認をすべきである "
				<< getRuntimeLineNumber()
				<< " 行目: "
				<< pImpl->m_ErrMap[mess_id]
				<< endl;
		}
	}

	bool Interpreter::isWorningOut() const {
		return pImpl->m_IsWorningOut;

	}
	void Interpreter::setWorningOut(bool b) {
		pImpl->m_IsWorningOut = b;
	}

}
//end namespace vv12