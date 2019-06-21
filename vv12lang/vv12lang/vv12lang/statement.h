#pragma once

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  ���^�C�v
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
	///  ���Ȃǂ̐e
	//--------------------------------------------------------------------------------------
	class StmExBase : public ObjBase {
	protected:
		StmExBase(ObjType type) :
			ObjBase(type) {}
	public:
		virtual ~StmExBase() {}
		//void�̎��s�֐�
		virtual SmtRes Excute() const {
			return SmtRes();
		}
	};

	//--------------------------------------------------------------------------------------
	///  ��
	//--------------------------------------------------------------------------------------
	class Statement : public StmExBase {
	protected:
		Statement(StatementType type);
	public:
		virtual ~Statement();
		StatementType getType()const;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};


	//--------------------------------------------------------------------------------------
	///  �����X�g�N���X
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
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  �����N���X
	//--------------------------------------------------------------------------------------
	class ExpressionStm : public Statement {
	public:
		ExpressionStm(const Expression* exp);
		ExpressionStm();
		virtual ~ExpressionStm();
		const Expression* getExp()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  if���N���X
//--------------------------------------------------------------------------------------
	class IfStm : public Statement {
	public:
		IfStm(const Expression* condition, const Statement* stm);
		virtual ~IfStm();
		const Expression* getCondition()const;
		const Statement* getStatement()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  ifelse���N���X
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
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};




	//--------------------------------------------------------------------------------------
///  while���N���X
//--------------------------------------------------------------------------------------
	class WhileStm : public Statement {
	public:
		WhileStm(const Expression* condition, const Statement* stm);
		virtual ~WhileStm();
		const Expression* getCondition()const;
		const Statement* getStatement()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  for���N���X
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
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};



	//--------------------------------------------------------------------------------------
	///  continue���N���X
	//--------------------------------------------------------------------------------------
	class ContinueStm : public Statement {
	public:
		ContinueStm();
		virtual ~ContinueStm();
		virtual SmtRes Excute() const  override;
	};


	//--------------------------------------------------------------------------------------
///  break���N���X
//--------------------------------------------------------------------------------------
	class BreakStm : public Statement {
	public:
		BreakStm();
		virtual ~BreakStm();
		virtual SmtRes Excute() const  override;
	};




	//--------------------------------------------------------------------------------------
///  �u���b�N���N���X
//--------------------------------------------------------------------------------------
	class BlockStm : public Statement {
	public:
		BlockStm(StatementList* stml);
		BlockStm();
		virtual ~BlockStm();
		const StatementList* getStatementList()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  return���N���X
//--------------------------------------------------------------------------------------
	class ReturnStm : public Statement {
	public:
		ReturnStm();
		ReturnStm(const Expression* retexp);
		virtual ~ReturnStm();
		const Expression* getRetExp()const;
		virtual SmtRes Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  �p�����[�^���X�g�N���X
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
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};




	//--------------------------------------------------------------------------------------
///  function��`�N���X
//--------------------------------------------------------------------------------------
	class FunctionDefineStm : public Statement {
	public:
		FunctionDefineStm(const char* ident, const ParameterList* pml, const Statement* stm);
		virtual ~FunctionDefineStm();
		const ParameterList* getParamList() const;
		virtual SmtRes Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};




	//--------------------------------------------------------------------------------------
	///  print��
	//--------------------------------------------------------------------------------------
	class PrintStm : public Statement {
	public:
		PrintStm(const Expression* target, bool nflg);
		virtual ~PrintStm();
		const Expression* getExpression()const;
		bool getNflg() const;
		virtual SmtRes Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

}
//end namespace vv12