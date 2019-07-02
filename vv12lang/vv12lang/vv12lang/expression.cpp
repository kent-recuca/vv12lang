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
	///  式クラス
	//--------------------------------------------------------------------------------------
	struct Expression::Impl {
		ExpressionType m_ExpType;
		Impl() {
			m_ExpType = ExpressionType::noExp;
		}
	};

	Expression::Expression(ExpressionType type)
		:ObjBase(ObjType::ExpType),
		pImpl(new Impl)
	{
		pImpl->m_ExpType = type;
	}

	Expression::~Expression() {
		delete pImpl;
	}

	ExpressionType Expression::getType()const {
		return pImpl->m_ExpType;
	}

	//--------------------------------------------------------------------------------------
  ///  intリテラル式クラス
  //--------------------------------------------------------------------------------------
	struct IntLiteralExp::Impl {
		int m_IntValue;
	};

	IntLiteralExp::IntLiteralExp(int i) :
		Expression(ExpressionType::intLiteralExp),
		pImpl(new Impl)
	{
		pImpl->m_IntValue = i;
	}
	IntLiteralExp::~IntLiteralExp() {
		delete pImpl;
	}

	int IntLiteralExp::getIntValue()const {
		return pImpl->m_IntValue;
	}

	Value IntLiteralExp::Excute() const {
		setRuntimeLineNumber();
		return Value(pImpl->m_IntValue);
	}

	//--------------------------------------------------------------------------------------
	///  doubleリテラル式クラス
	//--------------------------------------------------------------------------------------
	struct DoubleLiteralExp::Impl {
		double m_DoubleValue;
	};

	DoubleLiteralExp::DoubleLiteralExp(double d)
		:Expression(ExpressionType::doubleLiteralExp),
		pImpl(new Impl)
	{
		pImpl->m_DoubleValue = d;
	}

	DoubleLiteralExp::~DoubleLiteralExp() {
		delete pImpl;
	}


	double DoubleLiteralExp::getDoubleValue()const {
		return pImpl->m_DoubleValue;
	}

	Value DoubleLiteralExp::Excute() const {
		setRuntimeLineNumber();
		return Value(pImpl->m_DoubleValue);
	}

	//--------------------------------------------------------------------------------------
	///  stringリテラル式クラス
	//--------------------------------------------------------------------------------------
	struct StringLiteralExp::Impl {
		string m_StringLiteral;
	};

	StringLiteralExp::StringLiteralExp(const char* str) :
		Expression(ExpressionType::stringLiteralExp),
		pImpl(new Impl)
	{
		pImpl->m_StringLiteral = str;
	}
	StringLiteralExp::~StringLiteralExp() {
		delete pImpl;
	}

	const char* StringLiteralExp::getStringLiteral()const {
		return pImpl->m_StringLiteral.c_str();
	}

	Value StringLiteralExp::Excute() const {
		setRuntimeLineNumber();
		return Value(pImpl->m_StringLiteral.c_str());
	}

	//--------------------------------------------------------------------------------------
	///  識別子式クラス
	//--------------------------------------------------------------------------------------
	struct VariableExp::Impl {
		const char*  m_VariableName;
		bool m_Local;
	};

	VariableExp::VariableExp(const char* ident, bool local)
		:Expression(ExpressionType::variableExp),
		pImpl(new Impl)
	{
		pImpl->m_VariableName = Interpreter::getInp()->createFixedString(ident);
		pImpl->m_Local = local;
	}

	VariableExp::~VariableExp() {
		delete pImpl;
	}

	const char* VariableExp::getIdentifier()const {
		return pImpl->m_VariableName;
	}

	bool VariableExp::IsLocal() const {
		return pImpl->m_Local;
	}


	Value& VariableExp::getVariableValue() const {
		if (IsLocal()) {
			return Interpreter::getInp()->getLocalValiableValue(pImpl->m_VariableName);
		}
		else {
			if (Interpreter::getInp()->findLocalValiableValue(pImpl->m_VariableName)) {
				return Interpreter::getInp()->getLocalValiableValue(pImpl->m_VariableName);
			}
			return Interpreter::getInp()->getGlobalValiableValue(pImpl->m_VariableName);
		}
	}

	Value VariableExp::Excute() const {
		setRuntimeLineNumber();
		Value ret = getVariableValue();
		return ret;
	}

	//--------------------------------------------------------------------------------------
///  配列添え字と値ペアクラス
//--------------------------------------------------------------------------------------
	struct ArrKeyValueList::Impl {
		const Expression* m_Key;
		const Expression* m_Value;
		ArrKeyValueList* m_Next;
		Value tempVal;
	};

	ArrKeyValueList::ArrKeyValueList(const Expression* key, const Expression* value) :
		ObjBase(ObjType::ArrKeyValueListType),
		pImpl(new Impl)
	{
		pImpl->m_Key = key;
		pImpl->m_Value = value;
		pImpl->m_Next = nullptr;

	}
	ArrKeyValueList::~ArrKeyValueList() {
		delete pImpl;
	}

	const Expression* ArrKeyValueList::getKey() const {
		return pImpl->m_Key;

	}
	const Expression* ArrKeyValueList::getValue() const {
		return pImpl->m_Value;

	}
	ArrKeyValueList* ArrKeyValueList::getNext()const {
		return pImpl->m_Next;

	}
	void ArrKeyValueList::setNext(ArrKeyValueList* next) {
		pImpl->m_Next = next;
	}

	//--------------------------------------------------------------------------------------
///  array式(Valueのみ)
//--------------------------------------------------------------------------------------
	struct ArrayInitValueExp::Impl {
		const ArgumentList* m_ArgumentList;
	};

	ArrayInitValueExp::ArrayInitValueExp(const ArgumentList* argumentList) :
		Expression(ExpressionType::arrayInitValueExp),
		pImpl(new Impl)
	{
		pImpl->m_ArgumentList = argumentList;
	}

	ArrayInitValueExp::~ArrayInitValueExp()
	{
		delete pImpl;
	}

	const ArgumentList* ArrayInitValueExp::getArgumentList()const {
		return pImpl->m_ArgumentList;
	}

	Value ArrayInitValueExp::Excute() const {
		Value retValue;
		retValue.setArrClear();
		if (getArgumentList() != nullptr && getArgumentList()->getExp() != nullptr) {
			auto pos = getArgumentList();
			size_t count = 0;
			while (pos) {
				auto val = pos->getExp()->Excute();
				retValue.createArrKey(count);
				retValue[count] = val;
				pos = pos->getNext();
				count++;
			}
		}
		return retValue;
	}



	//--------------------------------------------------------------------------------------
///  array式(KeyとValue)
//--------------------------------------------------------------------------------------
	struct ArrayInitKeyValueExp::Impl {
		const ArrKeyValueList* m_ArrKeyValueList;
		Value tempVal;
	};


	ArrayInitKeyValueExp::ArrayInitKeyValueExp(const ArrKeyValueList* arrKeyValueList) :
		Expression(ExpressionType::arrayInitKeyValueExp),
		pImpl(new Impl)
	{
		pImpl->m_ArrKeyValueList = arrKeyValueList;
	}
	ArrayInitKeyValueExp::~ArrayInitKeyValueExp() {
		delete pImpl;
	}

	const ArrKeyValueList* ArrayInitKeyValueExp::getArrKeyValueList()const {
		return pImpl->m_ArrKeyValueList;
	}

	Value ArrayInitKeyValueExp::Excute() const {
		Value retVal;
		retVal.setArrClear();
		auto pos = getArrKeyValueList();
		while (pos) {
			auto key = pos->getKey()->Excute();
			auto val = pos->getValue()->Excute();
			if (key.getType() == ValueType::intVal && key.getInt() >= 0) {
				retVal.createArrKey((size_t)key.getInt());
				retVal[(size_t)key.getInt()] = val;
			}
			else if (key.getType() == ValueType::stringVal) {
				//文字列であってもsize_tに変換できるのならsize_tとして処理
				int chkInt = key.getInt();
				if (chkInt >= 0) {
					retVal.createArrKey((size_t)chkInt);
					retVal[(size_t)chkInt] = val;
				}
				else {
					retVal.createArrKey(key.getString());
					retVal[key.getString()] = val;
				}
			}
			else {
				Interpreter::getInp()->runtimeExit(2019);
				return pImpl->tempVal;
			}
			pos = pos->getNext();
		}
		return retVal;
	}

	//--------------------------------------------------------------------------------------
///  配列添え字クラス
//--------------------------------------------------------------------------------------
	struct ArrKeytList::Impl {
		const Expression* m_Key;
		ArrKeytList* m_Next;
		Value tempVal;
	};

	ArrKeytList::ArrKeytList() :
		ObjBase(ObjType::ArrKeyListType),
		pImpl(new Impl)
	{
		pImpl->m_Key = nullptr;
		pImpl->m_Next = nullptr;
	}

	ArrKeytList::ArrKeytList(const Expression* key) :
		ObjBase(ObjType::ArrKeyListType),
		pImpl(new Impl)
	{
		pImpl->m_Key = key;
		pImpl->m_Next = nullptr;
	}

	ArrKeytList::~ArrKeytList() {
		delete pImpl;
	}

	const Expression* ArrKeytList::getKey() const {
		return pImpl->m_Key;
	}
	ArrKeytList* ArrKeytList::getNext()const {
		return pImpl->m_Next;
	}

	void ArrKeytList::setNext(ArrKeytList* next) {
		pImpl->m_Next = next;
	}

	Value& ArrKeytList::getValue(Value& parent) {
		Value v;
		if (getKey()) {
			v = getKey()->Excute();
		}
		else {
			v = (int)parent.getNextIndexKey();
		}
		if (v.getType() == ValueType::intVal && v.getInt() >= 0) {
			if (getNext()) {
				return getNext()->getValue(parent[(size_t)v.getInt()]);
			}
			else {
				return parent[(size_t)v.getInt()];
			}
		}
		else if (v.getType() == ValueType::stringVal) {
			//文字列であってもsize_tに変換できるのならsize_tとして処理
			int chkInt = v.getInt();
			if (chkInt >= 0) {
				if (getNext()) {
					return getNext()->getValue(parent[(size_t)v.getInt()]);
				}
				else {
					return parent[(size_t)v.getInt()];
				}
			}
			else {
				if (getNext()) {
					return getNext()->getValue(parent[v.getString()]);
				}
				else {
					return parent[v.getString()];
				}
			}
		}
		else {
			Interpreter::getInp()->runtimeExit(2019);
			return pImpl->tempVal;
		}
	}

	//--------------------------------------------------------------------------------------
///  配列変数式クラス
//--------------------------------------------------------------------------------------
	struct ArrayExp::Impl {
		const char*  m_VariableName;
		bool m_Local;
		ArrKeytList* m_ArrKeytList;
		Value tempVal;
	};
	ArrayExp::ArrayExp(const char* ident, ArrKeytList* key, bool local) :
		Expression(ExpressionType::arrayExp),
		pImpl(new Impl)
	{
		pImpl->m_VariableName = Interpreter::getInp()->createFixedString(ident);
		pImpl->m_ArrKeytList = key;
		pImpl->m_Local = local;
	}
	ArrayExp::~ArrayExp() {
		delete pImpl;

	}
	const char* ArrayExp::getIdentifier()const {
		return pImpl->m_VariableName;
	}
	bool ArrayExp::IsLocal() const {
		return pImpl->m_Local;

	}

	Value& ArrayExp::getValue()const {
		if (IsLocal()) {
			return pImpl->m_ArrKeytList->getValue(Interpreter::getInp()->getLocalValiableValue(pImpl->m_VariableName));
		}
		else {
			if (Interpreter::getInp()->findLocalValiableValue(pImpl->m_VariableName)) {
				return pImpl->m_ArrKeytList->getValue(Interpreter::getInp()->getLocalValiableValue(pImpl->m_VariableName));
			}
			return pImpl->m_ArrKeytList->getValue(Interpreter::getInp()->getGlobalValiableValue(pImpl->m_VariableName));
		}
	}
	Value ArrayExp::Excute() const {
		setRuntimeLineNumber();
		Value ret = getValue();
		return ret;
	}



	//--------------------------------------------------------------------------------------
	///  代入式クラス
	//--------------------------------------------------------------------------------------
	struct AssignExp::Impl {
		const Expression* m_Variable;
		const Expression* m_Operand;
	};

	AssignExp::AssignExp(const Expression* variable, const Expression* operand)
		:Expression(ExpressionType::assignExp),
		pImpl(new Impl)
	{
		pImpl->m_Variable = variable;
		pImpl->m_Operand = operand;
	}

	AssignExp::~AssignExp() {
		delete pImpl;
	}

	const Expression* AssignExp::getVariable()const {
		return pImpl->m_Variable;
	}

	const Expression* AssignExp::getOperand()const {
		return pImpl->m_Operand;
	}

	Value AssignExp::Excute() const {
		setRuntimeLineNumber();
		//変数の値の参照を取り出す
		auto valptr = dynamic_cast<const VariableExp*>(pImpl->m_Variable);
		if (valptr) {
			Value& v = valptr->getVariableValue();
			v = pImpl->m_Operand->Excute();
			//それを返す
			return v;
		}
		return Value();
	}

	//--------------------------------------------------------------------------------------
///  配列代入式クラス
//--------------------------------------------------------------------------------------
	struct AssignArrExp::Impl {
		const Expression* m_Variable;
		const Expression* m_Operand;
	};

	AssignArrExp::AssignArrExp(const Expression* variable, const Expression* operand)
		:Expression(ExpressionType::assignExp),
		pImpl(new Impl)
	{
		pImpl->m_Variable = variable;
		pImpl->m_Operand = operand;
	}

	AssignArrExp::~AssignArrExp() {
		delete pImpl;
	}

	const Expression* AssignArrExp::getVariable()const {
		return pImpl->m_Variable;
	}

	const Expression* AssignArrExp::getOperand()const {
		return pImpl->m_Operand;
	}

	Value AssignArrExp::Excute() const {
		setRuntimeLineNumber();
		//変数の値の参照を取り出す
		auto valptr = dynamic_cast<const ArrayExp*>(pImpl->m_Variable);
		if (valptr) {
			Value& v = valptr->getValue();
			v = pImpl->m_Operand->Excute();
			//それを返す
			return v;
		}
		return Value();
	}


	//--------------------------------------------------------------------------------------
///  関係式クラス
//--------------------------------------------------------------------------------------
	struct RelationalExp::Impl {
		const Expression* m_Left;
		const Expression* m_Right;
	};

	RelationalExp::RelationalExp(ExpressionType type, const Expression* left, const Expression* right)
		:Expression(type),
		pImpl(new Impl)
	{
		pImpl->m_Left = left;
		pImpl->m_Right = right;
	}

	RelationalExp::~RelationalExp() {
		delete pImpl;

	}

	const Expression* RelationalExp::getLeft()const {
		return pImpl->m_Left;
	}

	const Expression* RelationalExp::getRight()const {
		return pImpl->m_Right;
	}

	Value RelationalExp::Excute() const {
		setRuntimeLineNumber();
		switch (getType()) {
		case ExpressionType::eqExp:
			// ==
			return Value(pImpl->m_Left->Excute() == pImpl->m_Right->Excute());
			break;
		case ExpressionType::neExp:
			// !=
			return Value(pImpl->m_Left->Excute() != pImpl->m_Right->Excute());
			break;
		case ExpressionType::ltExp:
			// <
			return Value(pImpl->m_Left->Excute() < pImpl->m_Right->Excute());
			break;
		case ExpressionType::gtExp:
			// >
			return Value(pImpl->m_Left->Excute() > pImpl->m_Right->Excute());
			break;
		case ExpressionType::leExp:
			// <=
			return Value(pImpl->m_Left->Excute() <= pImpl->m_Right->Excute());
			break;
		case ExpressionType::geExp:
			// >=
			return Value(pImpl->m_Left->Excute() >= pImpl->m_Right->Excute());
			break;
		}
		Interpreter::getInp()->runtimeExit(2010);
		return Value();
	}


	//--------------------------------------------------------------------------------------
	///  追演算クラス
	//--------------------------------------------------------------------------------------
	struct ToAssExp::Impl {
		const Expression* m_Variable;
		const Expression* m_Operand;
		ExpressionType m_ExpType;
	};

	ToAssExp::ToAssExp(const Expression* variable, const Expression* operand, ExpressionType tp)
		:Expression(ExpressionType::assignExp),
		pImpl(new Impl)
	{
		pImpl->m_Variable = variable;
		pImpl->m_Operand = operand;
		pImpl->m_ExpType = tp;
	}

	ToAssExp::~ToAssExp() {
		delete pImpl;
	}

	const Expression* ToAssExp::getVariable()const {
		return pImpl->m_Variable;
	}

	const Expression* ToAssExp::getOperand()const {
		return pImpl->m_Operand;
	}

	ExpressionType ToAssExp::getExpType()const {
		return pImpl->m_ExpType;
	}

	Value ToAssExp::Excute() const {
		setRuntimeLineNumber();
		//変数の値の参照を取り出す
		auto valptr = dynamic_cast<const VariableExp*>(pImpl->m_Variable);
		if (valptr) {
			Value& v = valptr->getVariableValue();
			switch (pImpl->m_ExpType) {
			case ExpressionType::addAssExp:
				//参照に追加算
				v += pImpl->m_Operand->Excute();
				break;
			case ExpressionType::subAssExp:
				//参照に追減算
				v -= pImpl->m_Operand->Excute();
				break;
			case ExpressionType::mulAssExp:
				//参照に追乗算
				v *= pImpl->m_Operand->Excute();
				break;
			case ExpressionType::divAssExp:
				//参照に追除算
				v /= pImpl->m_Operand->Excute();
				break;
			}
			//それを返す
			return v;
		}
		return Value();
	}

	//--------------------------------------------------------------------------------------
	///  演算式クラス
	//--------------------------------------------------------------------------------------
	struct BinaryExp::Impl {
		const Expression* m_Left;
		const Expression* m_Right;
	};

	BinaryExp::BinaryExp(ExpressionType type, const Expression* left, const Expression* right)
		:Expression(type),
		pImpl(new Impl)
	{
		pImpl->m_Left = left;
		pImpl->m_Right = right;
	}

	BinaryExp::~BinaryExp() {
		delete pImpl;

	}

	const Expression* BinaryExp::getLeft()const {
		return pImpl->m_Left;
	}

	const Expression* BinaryExp::getRight()const {
		return pImpl->m_Right;
	}

	Value BinaryExp::Excute() const {
		setRuntimeLineNumber();
		switch (getType()) {
		case ExpressionType::addExp:
			return (pImpl->m_Left->Excute() + pImpl->m_Right->Excute());
			break;
		case ExpressionType::subExp:
			return (pImpl->m_Left->Excute() - pImpl->m_Right->Excute());
			break;
		case ExpressionType::mulExp:
			return (pImpl->m_Left->Excute() * pImpl->m_Right->Excute());
			break;
		case ExpressionType::divExp:
			return (pImpl->m_Left->Excute() / pImpl->m_Right->Excute());
			break;
		}
		Interpreter::getInp()->runtimeExit(2004);
		return Value();
	}

	//--------------------------------------------------------------------------------------
///  引数クラス
//--------------------------------------------------------------------------------------
	struct ArgumentList::Impl {
		const Expression* m_Expression;
		ArgumentList* m_Next;
	};

	ArgumentList::ArgumentList() :
		ObjBase(ObjType::ParamListType),
		pImpl(new Impl)
	{
		pImpl->m_Expression = nullptr;
		pImpl->m_Next = nullptr;
	}

	ArgumentList::ArgumentList(const Expression* exp) :
		ObjBase(ObjType::ParamListType),
		pImpl(new Impl)
	{
		pImpl->m_Expression = exp;
		pImpl->m_Next = nullptr;
	}

	ArgumentList::~ArgumentList() {
		delete pImpl;
	}

	const Expression* ArgumentList::getExp() const {
		//nullptrの場合あり
		return pImpl->m_Expression;
	}

	ArgumentList* ArgumentList::getNext()const {
		return pImpl->m_Next;
	}

	void ArgumentList::setNext(ArgumentList* next) {
		pImpl->m_Next = next;
	}

	//--------------------------------------------------------------------------------------
	///  関数呼び出し式クラス
	//--------------------------------------------------------------------------------------
	struct FunctionCallExp::Impl {
		const char* m_Identifier;
		const ArgumentList* m_Argument;
		const FunctionDefineStm* m_FuncDef;
	};

	FunctionCallExp::FunctionCallExp(const char* ident, const ArgumentList* args, const FunctionDefineStm* funcDef)
		:Expression(ExpressionType::functionExp),
		pImpl(new Impl)
	{
		pImpl->m_Identifier = Interpreter::getInp()->createFixedString(ident);
		pImpl->m_Argument = args;
		pImpl->m_FuncDef = funcDef;
	}

	FunctionCallExp::~FunctionCallExp() {
		delete pImpl;
	}
	const char* FunctionCallExp::getIdentifier()const {
		//nullptrの場合あり
		return pImpl->m_Identifier;
	}

	Value FunctionCallExp::Excute() const {
		//関数呼び出しはは一つ階層を下がる
		Interpreter::getInp()->pushRuntime(true);
		//引数リストをローカル変数に作成
		auto argList = pImpl->m_Argument;
		auto paramlist = pImpl->m_FuncDef->getParamList();
		while (argList) {
			if (!paramlist) {
				//パラメータリストがなかった。
				//行き数の数がパラメータ数を上回っている。
				Interpreter::getInp()->runtimeExit(2013);
			}
			if (paramlist->getIdent()) {
				if (argList->getExp()) {
					Value& v = Interpreter::getInp()->getLocalValiableValue(paramlist->getIdent());
					v = argList->getExp()->Excute();
				}
				else {
					break;
				}
			}
			else {
				//パラメータリストがなかった。
				//行き数の数がパラメータ数を上回っている。
				Interpreter::getInp()->runtimeExit(2013);
			}
			argList = argList->getNext();
			paramlist = paramlist->getNext();
		}
		auto val = pImpl->m_FuncDef->Excute().m_RetValue;
		//終了前に一つ階層を上がる
		Interpreter::getInp()->popRuntime();
		return val;
	}


}
//end namespace vv12