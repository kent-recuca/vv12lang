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
				if (typeid(*stm) != typeid(FunctionDefineStm)) {
					stm->Excute();
				}
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
		map<string, FunctionDefineStm*> m_FunctionMap;

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
		//今関数の実行中かどうか
		bool m_FunctionRuntime;
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
			{ 0001, "を確認すべきだヨ(^^)/心配だなあ" },
			{ 0002, "その手前かもしれないネ(>_<)" },
			{ 1001, "ファイルの名前が指定されてないカモ(^^。" },
			{ 1002, "ファイルを読めなかったヨ(^o^)。" },
			{ 1003, "書きかた間違ってるヨ。" },
			{ 1004, "関数名はすでに使われているんだよね～～('ω')ノ。"},
			{ 1005, "関数が見つからないよ！。ない関数を呼んだってだめ！。呼ぶところより上で作らなきゃね('ω')。"},
			{ 2001, "実行文がないからなァ・・・動かせないよ(;'∀')" },
			{ 2002, "おじさんには若い子のことはなんだかわからないよ(-_-;)" },
			{ 2003, "0では割れないよん。" },
			{ 2004, "演算できないな！"},
			{ 2005, "右辺が負の数だと文字列の掛け算はできないんだよ。正の数字ならできるヨ。" },
			{ 2006, "左辺が文字列だと引き算できないよ。足し算か掛け算ならできるヨ。" },
			{ 2007, "左辺が文字列だと割り算できないよ。足し算か掛け算ならできるんじゃないかなァ。" },
			{ 2008, "bool型はほかの型とは比較できないよ。bool同士ならできるカモ。" },
			{ 2009, "文字列は比較できないんだ" },
			{ 2010, "比較演算ができないよ"},
			{ 2011, "ローカル変数は関数のなかでしか作れないよ。"},
			{ 2012, "定義関数で、キーが空白じゃないかナ？"},
			{ 2013, "関数呼び出しで、パラメータ数より実引数が多いなあ？。関数定義をよくみてみてよ。"},
			{ 2014, "関数のながに関数をつくろうとしてる？？。ごめんね、おじさんには無理だよ。"},
			{ 2015, "なんだかわからないや、ループがスイッチが開閉がなってないカモ？？。"},
			{ 2016, "ブレーク文はループの中がスイッチの中じゃないとネ。"},
			{ 2017, "リターン文は関数内でしか書けないよ。"},
			{ 2018, "コンティニュー文はループの中しか書けないよ。"},
			{ 2019, "配列の添え字は正の整数か文字列だね"},
			{ 2020, "親配列がないな！"},
			{ 2021, "配列はほかの型に変換できないヨ。"},
			{ 2022, "その配列の添え字はないよ。"},
		};

		//初期状態はワーニングを出す
		pImpl->m_IsWorningOut = true;
		pImpl->m_RuntimeLineNumber = 1;
		pImpl->m_TempVal = Value();
		pImpl->m_ConfigMap["calc_epsilon"] = "0.000001";
		pImpl->m_FunctionRuntime = false;
		pImpl->m_BreakDeps = 0;
		pImpl->m_LoopDeps = 0;
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
			pImpl->m_RootRuntime = pImpl->m_CurrentRuntime;
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

	//continue可能かどうか
	bool Interpreter::isContinueOK() const {
		if (pImpl->m_LoopDeps > 0) {
			return true;
		}
		return false;
	}


	bool Interpreter::isBreakOK() const {
		if (pImpl->m_BreakDeps > 0) {
			return true;
		}
		return false;
	}

	void Interpreter::setFunctionRuntime(bool b) {
		pImpl->m_FunctionRuntime = b;

	}

	bool Interpreter::isFunctionRuntime() const {
		return pImpl->m_FunctionRuntime;
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

	Expression* Interpreter::createVariableExp(const char* ident, bool isLocal) {
		string str = clampToken(ident);
		auto ptr = new VariableExp(str.c_str(),isLocal);
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

	Expression* Interpreter::createRelationalExp(const Expression* left, const Expression* right, ExpressionType t) {
		auto ptr = new RelationalExp(t, left, right);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}


	Expression* Interpreter::createAssExp(const Expression* ident, const Expression* right) {
		auto ptr = new AssignExp(ident, right);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	Expression* Interpreter::createAssignArrExp(const Expression* variable, const Expression* operand) {
		auto ptr = new AssignArrExp(variable, operand);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}


	Expression* Interpreter::createToAssExp(const Expression* ident, const Expression* right, ExpressionType t) {
		auto ptr = new ToAssExp(ident, right, t);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	ArgumentList* Interpreter::createArgumentList() {
		auto ptr = new ArgumentList();
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	ArgumentList* Interpreter::createArgumentList(const Expression* exp) {
		auto ptr = new ArgumentList(exp);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;

	}

	ArgumentList* Interpreter::createArgumentList(ArgumentList* agl, const Expression* exp) {
		ArgumentList* pos;
		if (agl == nullptr)
			return createArgumentList(exp);
		for (pos = agl; pos->getNext(); pos = pos->getNext())
			;
		pos->setNext(createArgumentList(exp));
		return agl;
	}

	Expression* Interpreter::createArrayInitValueExp(const ArgumentList* argumentList) {
		auto ptr = new ArrayInitValueExp(argumentList);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	Expression* Interpreter::createArrayInitKeyValueExp(const ArrKeyValueList* arrKeyValueList) {
		auto ptr = new ArrayInitKeyValueExp(arrKeyValueList);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	ArrKeyValueList* Interpreter::createArrKeyValueList(const Expression* key, const Expression* value) {
		auto ptr = new ArrKeyValueList(key, value);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	ArrKeyValueList* Interpreter::createArrKeyValueList(ArrKeyValueList* prev, const Expression* key, const Expression* value) {
		ArrKeyValueList* pos;
		if (prev == nullptr)
			return createArrKeyValueList(key, value);
		for (pos = prev; pos->getNext(); pos = pos->getNext())
			;
		pos->setNext(createArrKeyValueList(key, value));
		return prev;
	}

	ArrKeytList* Interpreter::createArrKeytList() {
		auto ptr = new ArrKeytList();
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	ArrKeytList* Interpreter::createArrKeytList(const Expression* key) {
		auto ptr = new ArrKeytList(key);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}
	ArrKeytList* Interpreter::createArrKeytList(ArrKeytList* parent, const Expression* key) {
		ArrKeytList* pos;
		if (parent == nullptr)
			return createArrKeytList(key);
		for (pos = parent; pos->getNext(); pos = pos->getNext())
			;
		pos->setNext(createArrKeytList(key));
		return parent;
	}


	Expression* Interpreter::createArrayExp(const char* ident, ArrKeytList* keylist, bool isLocal) {
		string str = clampToken(ident);
		auto ptr = new ArrayExp(str.c_str(), keylist, isLocal);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}



	Expression* Interpreter::createFunctionCallExp(const char* ident, const ArgumentList* args) {
		extern int gLine;
		auto it = pImpl->m_FunctionMap.find(ident);
		if (it == pImpl->m_FunctionMap.end()) {
			//その名前の関数がなかった
			syntaxExit(1005, gLine, ident, false);
		}
		auto ptr = new FunctionCallExp(ident, args, pImpl->m_FunctionMap[ident]);
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

	ParameterList* Interpreter::createParameterList() {
		auto ptr = new ParameterList();
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	ParameterList* Interpreter::createParameterList(const char* ident) {
		auto ptr = new ParameterList(ident);
		pImpl->m_ObjectPool.push_back(ptr);
		return ptr;
	}

	ParameterList* Interpreter::createParameterList(ParameterList* pml, const char* ident) {
		ParameterList *pos;
		if (pml == nullptr)
			return createParameterList(ident);
		for (pos = pml; pos->getNext(); pos = pos->getNext())
			;
		pos->setNext(createParameterList(ident));
		return pml;
	}

	
	Statement* Interpreter::createFunctionDefineStm(const char* ident, const ParameterList* pml, const Statement* stm) {
		extern int gLine;
		auto it = pImpl->m_FunctionMap.find(ident);
		if (it != pImpl->m_FunctionMap.end()) {
			//すでにその名前の関数があった
			syntaxExit(1004, gLine, ident, false);
		}
		auto ptr = new FunctionDefineStm(ident, pml, stm);
		pImpl->m_ObjectPool.push_back(ptr);
		pImpl->m_FunctionMap[ident] = ptr;
		return ptr;
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

	bool Interpreter::findLocalValiableValue(const char* key) {
		auto tgtRuntime = pImpl->m_CurrentRuntime;
		do {
			if (tgtRuntime->m_IsFunc) {
				auto it = tgtRuntime->m_VariableMap.find(key);
				if (it != tgtRuntime->m_VariableMap.end()) {
					//見つかった
					return true;
				}
				else {
					return false;
				}
			}
			tgtRuntime = tgtRuntime->m_Parent.lock();
		} while (tgtRuntime);
		//ルートまでさかのぼってしまった。
		return false;
	}

	Value& Interpreter::getLocalValiableValue(const char* key) {
		auto tgtRuntime = pImpl->m_CurrentRuntime;
		do {
			if (tgtRuntime->m_IsFunc) {
				auto it = tgtRuntime->m_VariableMap.find(key);
				if (it != tgtRuntime->m_VariableMap.end()) {
					//見つかった
					return it->second;
				}
				else {
					//無かったので作成
					//stringで作成
					tgtRuntime->m_VariableMap[key] = Value("");
					return tgtRuntime->m_VariableMap[key];
				}
			}
			tgtRuntime = tgtRuntime->m_Parent.lock();
		} while (tgtRuntime);
		//ルートまでさかのぼってしまった。
		runtimeExit(2011, key);
		return pImpl->m_TempVal;
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
			cerr << "\n動かしてるときのマチガイだよ^^。 "
				<< getRuntimeLineNumber()
				<< " 行目: "
				<< target
				<< " "
				<< pImpl->m_ErrMap[mess_id]
				<< endl;

		}
		else {
			cerr << "\n動かしてるときのマチガイだよ^^。 "
				<< getRuntimeLineNumber()
				<< " 行目: "
				<< pImpl->m_ErrMap[mess_id]
				<< endl;

		}
		exit(1);
	}

	void Interpreter::runtimeWorning(int mess_id) {
		if (isWorningOut()) {
			cerr << "\n動かしてるときのマチガイだよ^^。いちおう言っておくネ(^^) "
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