#pragma once

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  文タイプ
	//--------------------------------------------------------------------------------------
	enum class StatementType {
		nullStm,
		expressionStm,
		whileStm,
		ifStm,
		forStm,
		blockStm,
		continueStm,
		breakStm,
		returnStm,
		printStm,
		stmTypeCount
	};

	enum class SmtResType {
		voidType,
		continueType,
		breakType,
		returnTpe,
	};

	struct SmtRes {
		SmtResType m_Type;
		Value m_RetValue;
		SmtRes() :
			m_Type(SmtResType::voidType),
			m_RetValue() {}
	};

	//--------------------------------------------------------------------------------------
	///  文などの親
	//--------------------------------------------------------------------------------------
	class StmExBase : public ObjBase {
	protected:
		StmExBase(ObjType type) :
			ObjBase(type) {}
	public:
		virtual ~StmExBase() {}
		//voidの実行関数
		virtual SmtRes Excute() const {
			return SmtRes();
		}
	};

	//--------------------------------------------------------------------------------------
	///  文
	//--------------------------------------------------------------------------------------
	class Statement : public StmExBase {
	protected:
		Statement(StatementType type);
	public:
		virtual ~Statement();
		StatementType getType()const;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};


	//--------------------------------------------------------------------------------------
	///  文リストクラス
	//--------------------------------------------------------------------------------------
	class StatementList : public StmExBase {
	public:
		StatementList(const Statement* stm);
		virtual ~StatementList();
		const Statement* getStm() const;
		StatementList* getNext()const;
		void setNext(StatementList* next);
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  式文クラス
	//--------------------------------------------------------------------------------------
	class ExpressionStm : public Statement {
	public:
		ExpressionStm(const Expression* exp);
		ExpressionStm();
		virtual ~ExpressionStm();
		const Expression* getExp()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  if文クラス
//--------------------------------------------------------------------------------------
	class IfStm : public Statement {
	public:
		IfStm(const Expression* condition, const Statement* stm);
		virtual ~IfStm();
		const Expression* getCondition()const;
		const Statement* getStatement()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  ifelse文クラス
//--------------------------------------------------------------------------------------
	class IfElsStm : public Statement {
	public:
		IfElsStm(const Expression* condition, const Statement* stm, const Statement* elsstm);
		virtual ~IfElsStm();
		const Expression* getCondition()const;
		const Statement* getStatement()const;
		const Statement* getElsStatement()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};




	//--------------------------------------------------------------------------------------
///  while文クラス
//--------------------------------------------------------------------------------------
	class WhileStm : public Statement {
	public:
		WhileStm(const Expression* condition, const Statement* stm);
		virtual ~WhileStm();
		const Expression* getCondition()const;
		const Statement* getStatement()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  for文クラス
//--------------------------------------------------------------------------------------
	class ForStm : public Statement {
	public:
		ForStm(const Statement* initstm, const Expression* condition, const Expression* post, const Statement* stm);
		virtual ~ForStm();
		const Statement* getInitStatement()const;
		const Expression* getCondition()const;
		const Expression* getPost()const;
		const Statement* getStatement()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};



	//--------------------------------------------------------------------------------------
	///  continue文クラス
	//--------------------------------------------------------------------------------------
	class ContinueStm : public Statement {
	public:
		ContinueStm();
		virtual ~ContinueStm();
		virtual SmtRes Excute() const  override;
	};


	//--------------------------------------------------------------------------------------
///  break文クラス
//--------------------------------------------------------------------------------------
	class BreakStm : public Statement {
	public:
		BreakStm();
		virtual ~BreakStm();
		virtual SmtRes Excute() const  override;
	};




	//--------------------------------------------------------------------------------------
///  ブロック文クラス
//--------------------------------------------------------------------------------------
	class BlockStm : public Statement {
	public:
		BlockStm(StatementList* stml);
		BlockStm();
		virtual ~BlockStm();
		const StatementList* getStatementList()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  return文クラス
//--------------------------------------------------------------------------------------
	class ReturnStm : public Statement {
	public:
		ReturnStm();
		ReturnStm(const Expression* retexp);
		virtual ~ReturnStm();
		const Expression* getRetExp()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  パラメータリストクラス
//--------------------------------------------------------------------------------------
	class ParameterList : public ObjBase {
	public:
		ParameterList();
		ParameterList(const char* ident);
		virtual ~ParameterList();
		const char* getIdent() const;
		ParameterList* getNext()const;
		void setNext(ParameterList* next);
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};




	//--------------------------------------------------------------------------------------
///  function定義クラス
//--------------------------------------------------------------------------------------
	class FunctionDefineStm : public Statement {
	public:
		FunctionDefineStm(const char* ident, const ParameterList* pml, const Statement* stm);
		virtual ~FunctionDefineStm();
		const ParameterList* getParamList() const;
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};




	//--------------------------------------------------------------------------------------
	///  print文
	//--------------------------------------------------------------------------------------
	class PrintStm : public Statement {
	public:
		PrintStm(const Expression* target, bool nflg);
		virtual ~PrintStm();
		const Expression* getExpression()const;
		bool getNflg() const;
		virtual SmtRes Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

}
//end namespace vv12