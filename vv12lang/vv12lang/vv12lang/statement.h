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
		printStm,
		stmTypeCount
	};

	enum class SmtResType {
		voidType,
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