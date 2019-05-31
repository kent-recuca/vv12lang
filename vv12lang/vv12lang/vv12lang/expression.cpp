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
	};

	VariableExp::VariableExp(const char* ident)
		:Expression(ExpressionType::variableExp),
		pImpl(new Impl)
	{
		pImpl->m_VariableName = Interpreter::getInp()->createFixedString(ident);
	}

	VariableExp::~VariableExp() {
		delete pImpl;
	}

	const char* VariableExp::getIdentifier()const {
		return pImpl->m_VariableName;
	}

	Value& VariableExp::getVariableValue() const {
		return Interpreter::getInp()->getGlobalValiableValue(pImpl->m_VariableName);
	}

	Value VariableExp::Excute() const {
		setRuntimeLineNumber();
		Value ret = getVariableValue();
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


}
//end namespace vv12