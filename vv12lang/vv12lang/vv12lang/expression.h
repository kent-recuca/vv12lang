#pragma once

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  式タイプ
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
	///  式クラス
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
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
   ///  intリテラル式クラス
   //--------------------------------------------------------------------------------------
	class IntLiteralExp : public Expression {
	public:
		IntLiteralExp(int i = 0);
		virtual ~IntLiteralExp();
		int getIntValue()const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};


	//--------------------------------------------------------------------------------------
	///  doubleリテラル式クラス
	//--------------------------------------------------------------------------------------
	class DoubleLiteralExp : public Expression {
	public:
		DoubleLiteralExp(double d = 0.0);
		virtual ~DoubleLiteralExp();
		double getDoubleValue()const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  stringリテラル式クラス
	//--------------------------------------------------------------------------------------
	class StringLiteralExp : public Expression {
	public:
		StringLiteralExp(const char* str);
		virtual ~StringLiteralExp();
		const char* getStringLiteral() const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  変数式クラス
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
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};


	//--------------------------------------------------------------------------------------
	///  代入式クラス
	//--------------------------------------------------------------------------------------
	class AssignExp : public Expression {
	public:
		AssignExp(const Expression* variable, const Expression* operand);
		virtual ~AssignExp();
		const Expression* getVariable()const;
		const Expression* getOperand()const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};


	//--------------------------------------------------------------------------------------
	///  追演算クラス
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
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  演算式クラス
	//--------------------------------------------------------------------------------------
	class BinaryExp : public Expression {
	public:
		BinaryExp(ExpressionType type, const Expression* left, const Expression* right);
		virtual ~BinaryExp();
		const Expression* getLeft()const;
		const Expression* getRight()const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  関係式クラス
//--------------------------------------------------------------------------------------
	class RelationalExp : public Expression {
	public:
		RelationalExp(ExpressionType type, const Expression* left, const Expression* right);
		virtual ~RelationalExp();
		const Expression* getLeft()const;
		const Expression* getRight()const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  引数クラス
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
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  配列添え字と値ペアクラス
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
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  array式(Valueのみ)
//--------------------------------------------------------------------------------------
	class ArrayInitValueExp : public Expression {
	public:
		ArrayInitValueExp(const ArgumentList* argumentList);
		virtual ~ArrayInitValueExp();
		const ArgumentList* getArgumentList()const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};



	//--------------------------------------------------------------------------------------
///  array式(KeyとValue)
//--------------------------------------------------------------------------------------
	class ArrayInitKeyValueExp : public Expression {
	public:
		ArrayInitKeyValueExp(const ArrKeyValueList* arrKeyValueList);
		virtual ~ArrayInitKeyValueExp();
		const ArrKeyValueList* getArrKeyValueList()const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};


	//--------------------------------------------------------------------------------------
///  配列添え字クラス
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
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  配列変数式クラス
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
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
///  配列代入式クラス
//--------------------------------------------------------------------------------------
	class AssignArrExp : public Expression {
	public:
		AssignArrExp(const Expression* variable, const Expression* operand);
		virtual ~AssignArrExp();
		const Expression* getVariable()const;
		const Expression* getOperand()const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};





	class FunctionDefineStm;
	//--------------------------------------------------------------------------------------
///  関数呼び出し式クラス
//--------------------------------------------------------------------------------------
	class FunctionCallExp : public Expression {
	public:
		FunctionCallExp(const char* ident, const ArgumentList* args, const FunctionDefineStm* funcDef);
		virtual ~FunctionCallExp();
		const char* getIdentifier()const;
		virtual Value Excute() const  override;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};





}
//end namespace vv12