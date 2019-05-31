#pragma once

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  ���^�C�v
	//--------------------------------------------------------------------------------------
	enum class ExpressionType {
		noExp = 0,
		intLiteralExp,
		doubleLiteralExp,
		stringLiteralExp,
		variableExp,
		assignExp,
		addAssExp,
		subAssExp,
		mulAssExp,
		divAssExp,
		eqExp,
		neExp,
		gtExp,
		geExp,
		ltExp,
		leExp,
		addExp,
		subExp,
		mulExp,
		divExp,
		printExp,
		expTypeCount
	};

	//--------------------------------------------------------------------------------------
	///  ���N���X
	//--------------------------------------------------------------------------------------
	class Expression : public ObjBase {
	protected:
		Expression(ExpressionType type);
	public:
		virtual ~Expression();
		ExpressionType getType()const;
		virtual Value Excute() const {
			return Value();
		}
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
   ///  int���e�������N���X
   //--------------------------------------------------------------------------------------
	class IntLiteralExp : public Expression {
	public:
		IntLiteralExp(int i = 0);
		virtual ~IntLiteralExp();
		int getIntValue()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};


	//--------------------------------------------------------------------------------------
	///  double���e�������N���X
	//--------------------------------------------------------------------------------------
	class DoubleLiteralExp : public Expression {
	public:
		DoubleLiteralExp(double d = 0.0);
		virtual ~DoubleLiteralExp();
		double getDoubleValue()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  string���e�������N���X
	//--------------------------------------------------------------------------------------
	class StringLiteralExp : public Expression {
	public:
		StringLiteralExp(const char* str);
		virtual ~StringLiteralExp();
		const char* getStringLiteral() const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  �ϐ����N���X
	//--------------------------------------------------------------------------------------
	class VariableExp : public Expression {
	public:
		VariableExp(const char* ident);
		virtual ~VariableExp();
		const char* getIdentifier()const;
		Value& getVariableValue()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  ������N���X
	//--------------------------------------------------------------------------------------
	class AssignExp : public Expression {
	public:
		AssignExp(const Expression* variable, const Expression* operand);
		virtual ~AssignExp();
		const Expression* getVariable()const;
		const Expression* getOperand()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};


	//--------------------------------------------------------------------------------------
	///  �ǉ��Z�N���X
	//--------------------------------------------------------------------------------------
	class ToAssExp : public Expression {
	public:
		ToAssExp(const Expression* variable, const Expression* operand, ExpressionType tp);
		virtual ~ToAssExp();
		const Expression* getVariable()const;
		const Expression* getOperand()const;
		ExpressionType getExpType()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  ���Z���N���X
	//--------------------------------------------------------------------------------------
	class BinaryExp : public Expression {
	public:
		BinaryExp(ExpressionType type, const Expression* left, const Expression* right);
		virtual ~BinaryExp();
		const Expression* getLeft()const;
		const Expression* getRight()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  �֌W���N���X
//--------------------------------------------------------------------------------------
	class RelationalExp : public Expression {
	public:
		RelationalExp(ExpressionType type, const Expression* left, const Expression* right);
		virtual ~RelationalExp();
		const Expression* getLeft()const;
		const Expression* getRight()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};




}
//end namespace vv12