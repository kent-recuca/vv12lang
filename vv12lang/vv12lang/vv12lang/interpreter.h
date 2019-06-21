#pragma once

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  ルートクラス
	//--------------------------------------------------------------------------------------
	class Root : public StmExBase {
	public:
		Root(const StatementList* stml);
		virtual ~Root();
		virtual SmtRes Excute() const  override;
		const StatementList* getStmeList()const;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  インタープリタクラス
	//--------------------------------------------------------------------------------------
	class Interpreter : public ObjBase {
		Interpreter();
	public:
		virtual ~Interpreter();
		int Compile(FILE *fp);
		void Exec() const;
		void Delete();
		///Util
		void setConfig(const char* key, const Value val);
		Value getConfig(const char* key);
		void pushBackObject(ObjBase* pobj);
		const char* createFixedString(const char* ext);
		///Expression
		Expression* createVariableExp(const char* ident, bool isLocal);
		Expression* createIntLiteralExp(const char* ext);
		Expression* createDoubleLiteralExp(const char* ext);
		Expression* createBinaryExp(const Expression* left, const Expression* right, ExpressionType t);
		Expression* createRelationalExp(const Expression* left, const Expression* right, ExpressionType t);
		Expression* createAssExp(const Expression* ident, const Expression* right);
		Expression* createToAssExp(const Expression* ident, const Expression* right, ExpressionType t);
		ArgumentList* createArgumentList();
		ArgumentList* createArgumentList(const Expression* exp);
		ArgumentList* createArgumentList(ArgumentList* agl, const Expression* exp);
		Expression* createFunctionCallExp(const char* ident, const ArgumentList* args);


		//文字列リテラル
		void startStringLiteral();
		void addStringLiteral(char ext);
		Expression* createStringLiteralExp();

		///Statement
		//Util template
		template<typename T, typename... Ts>
		Statement* createStatement(Ts&&... params) {
			auto ptr = new T(params...);
			pushBackObject(ptr);
			return ptr;
		}

		ParameterList* createParameterList();
		ParameterList* createParameterList(const char* ident);
		ParameterList* createParameterList(ParameterList* pml, const char* ident);
		Statement* createFunctionDefineStm(const char* ident, const ParameterList* pml, const Statement* stm);

		///StatementList
		StatementList* createStatementList(const Statement* stm);
		StatementList* createStatementList(StatementList* stml, const Statement* stm);
		//Root
		Root*  createRoot(const StatementList* stml);
		//インスタンス参照
		static Interpreter* getInp();
		///Exec関連
		///変数の値の参照を取得
		Value& getGlobalValiableValue(const char* key);
		//ローカル変数に探す
		bool findLocalValiableValue(const char* key);
		///ローカル変数の値の参照を取得
		Value& getLocalValiableValue(const char* key);

		///１階層ランタイムをpushする
		void pushRuntime(bool IsFunc = false);
		///１階層ランタイムをpopする
		void popRuntime();

		//ループ実行中かどうか
		void pushLoop();
		void popLoop();
		//break可能な深さをpushする。
		void pushBreak();
		//break可能な深さをpopする。
		void popBreak();
		//continue可能かどうか
		bool isContinueOK() const;
		//break可能かどうか
		bool isBreakOK() const;

		//関数実行中かどうか
		void setFunctionRuntime(bool b);
		bool isFunctionRuntime() const;



		///シンタックスエラー予約語関連
		void syntaxKeepExit(int mess_id, const char* detail);
		///シンタックスエラー(行番号、位置情報付き)
		void syntaxExit(int mess_id, int linnum, const char* detail, bool bison = true);
		///ランタイム中の行番号
		void setRuntimeLineNumber(int num);
		int getRuntimeLineNumber() const;
		///ランタイムエラー(行番号付き)
		void runtimeExit(int mess_id, const char* target = nullptr);
		///ランタイムワーニング
		void runtimeWorning(int mess_id);
		///警告を出すかどうか
		bool isWorningOut() const;
		void setWorningOut(bool b);
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

}
//end namespace vv12