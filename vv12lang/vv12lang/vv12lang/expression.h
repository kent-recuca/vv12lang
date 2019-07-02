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
		arrayExp,
		arrayInitValueExp,
		arrayInitKeyValueExp,
		functionExp,
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
		VariableExp(const char* ident, bool local = false);
		virtual ~VariableExp();
		const char* getIdentifier()const;
		bool IsLocal() const;
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

	//--------------------------------------------------------------------------------------
///  �����N���X
//--------------------------------------------------------------------------------------
	class ArgumentList : public ObjBase {
	public:
		ArgumentList();
		ArgumentList(const Expression* exp);
		virtual ~ArgumentList();
		const Expression* getExp() const;
		ArgumentList* getNext()const;
		void setNext(ArgumentList* next);
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  �z��Y�����ƒl�y�A�N���X
//--------------------------------------------------------------------------------------
	class ArrKeyValueList : public ObjBase {
	public:
		ArrKeyValueList(const Expression* key, const Expression* value);
		virtual ~ArrKeyValueList();
		const Expression* getKey() const;
		const Expression* getValue() const;
		ArrKeyValueList* getNext()const;
		void setNext(ArrKeyValueList* next);
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  array��(Value�̂�)
//--------------------------------------------------------------------------------------
	class ArrayInitValueExp : public Expression {
	public:
		ArrayInitValueExp(const ArgumentList* argumentList);
		virtual ~ArrayInitValueExp();
		const ArgumentList* getArgumentList()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};



	//--------------------------------------------------------------------------------------
///  array��(Key��Value)
//--------------------------------------------------------------------------------------
	class ArrayInitKeyValueExp : public Expression {
	public:
		ArrayInitKeyValueExp(const ArrKeyValueList* arrKeyValueList);
		virtual ~ArrayInitKeyValueExp();
		const ArrKeyValueList* getArrKeyValueList()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};


	//--------------------------------------------------------------------------------------
///  �z��Y�����N���X
//--------------------------------------------------------------------------------------
	class ArrKeytList : public ObjBase {
	public:
		ArrKeytList();
		ArrKeytList(const Expression* key);
		virtual ~ArrKeytList();
		const Expression* getKey() const;
		Value& getValue(Value& parent);
		ArrKeytList* getNext()const;
		void setNext(ArrKeytList* next);
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  �z��ϐ����N���X
//--------------------------------------------------------------------------------------
	class ArrayExp : public Expression {
	public:
		ArrayExp(const char* ident, ArrKeytList* key, bool local = false);
		virtual ~ArrayExp();
		const char* getIdentifier()const;
		bool IsLocal() const;
		Value& getValue()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  �z�������N���X
//--------------------------------------------------------------------------------------
	class AssignArrExp : public Expression {
	public:
		AssignArrExp(const Expression* variable, const Expression* operand);
		virtual ~AssignArrExp();
		const Expression* getVariable()const;
		const Expression* getOperand()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};





	class FunctionDefineStm;
	//--------------------------------------------------------------------------------------
///  �֐��Ăяo�����N���X
//--------------------------------------------------------------------------------------
	class FunctionCallExp : public Expression {
	public:
		FunctionCallExp(const char* ident, const ArgumentList* args, const FunctionDefineStm* funcDef);
		virtual ~FunctionCallExp();
		const char* getIdentifier()const;
		virtual Value Excute() const  override;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};





}
//end namespace vv12