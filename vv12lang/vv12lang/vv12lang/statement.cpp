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
	///  文
	//--------------------------------------------------------------------------------------
	struct Statement::Impl {
		StatementType   m_StmType;
		int m_LineNumber;
	};

	Statement::Statement(StatementType type) :
		StmExBase(ObjType::StmType),
		pImpl(new Impl)
	{
		pImpl->m_StmType = type;
		pImpl->m_LineNumber = 0;
	}

	Statement::~Statement() {
		delete pImpl;
	}

	StatementType Statement::getType()const {
		return pImpl->m_StmType;
	}


	//--------------------------------------------------------------------------------------
	///  文リストクラス
	//--------------------------------------------------------------------------------------
	struct StatementList::Impl {
		const Statement* m_Statement;
		StatementList* m_Next;
	};

	StatementList::StatementList(const Statement* stm) :
		StmExBase(ObjType::StmListType),
		pImpl(new Impl)
	{
		pImpl->m_Statement = stm;
		pImpl->m_Next = nullptr;
	}

	StatementList::~StatementList() {
		delete pImpl;
	}

	const Statement* StatementList::getStm() const {
		return pImpl->m_Statement;
	}

	StatementList* StatementList::getNext()const {
		return pImpl->m_Next;
	}

	void StatementList::setNext(StatementList* next) {
		pImpl->m_Next = next;
	}

	SmtRes StatementList::Excute() const {
		setRuntimeLineNumber();
		auto stml = this;
		while (stml) {
			auto stm = stml->getStm();
			if (stm) {
					auto res = stm->Excute();
					if (res.m_Type == SmtResType::breakType || res.m_Type == SmtResType::returnTpe
						|| res.m_Type == SmtResType::continueType) {
						return res;
					}
			}
			else {
				break;
			}
			stml = stml->getNext();
		}
		return SmtRes();
	}

	//--------------------------------------------------------------------------------------
	///  式文クラス
	//--------------------------------------------------------------------------------------
	struct ExpressionStm::Impl {
		const Expression* m_Exp;
	};

	ExpressionStm::ExpressionStm()
		:Statement(StatementType::expressionStm),
		pImpl(nullptr)
	{
		//空文の場合はpImplは作成しない
	}

	ExpressionStm::ExpressionStm(const Expression* exp)
		:Statement(StatementType::expressionStm),
		pImpl(new Impl)
	{
		pImpl->m_Exp = exp;
	}

	ExpressionStm::~ExpressionStm() {
		delete pImpl;
	}

	const Expression* ExpressionStm::getExp()const {
		return pImpl->m_Exp;
	}

	SmtRes ExpressionStm::Excute() const {
		setRuntimeLineNumber();
		if (pImpl) {
			getExp()->Excute();
		}
		return SmtRes();
	}

	//--------------------------------------------------------------------------------------
///  if文クラス
//--------------------------------------------------------------------------------------
	struct IfStm::Impl {
		const Expression* m_Condition;
		const Statement* m_Statement;
	};

	IfStm::IfStm(const Expression* condition, const Statement* stm)
		: Statement(StatementType::ifStm),
		pImpl(new Impl)
	{
		pImpl->m_Condition = condition;
		pImpl->m_Statement = stm;
	}

	IfStm::~IfStm() {
		delete pImpl;

	}

	const Expression* IfStm::getCondition()const {
		return pImpl->m_Condition;
	}

	const Statement* IfStm::getStatement()const {
		return pImpl->m_Statement;
	}

	SmtRes IfStm::Excute() const {
		setRuntimeLineNumber();
		auto val = getCondition()->Excute();
		if (val.getBool()) {
			return getStatement()->Excute();
		}
		return SmtRes();
	}

	//--------------------------------------------------------------------------------------
///  ifelse文クラス
//--------------------------------------------------------------------------------------
	struct IfElsStm::Impl {
		const Expression* m_Condition;
		const Statement* m_Statement;
		const Statement* m_ElsStatement;
	};

	IfElsStm::IfElsStm(const Expression* condition, const Statement* stm, const Statement* elsstm)
		: Statement(StatementType::ifStm),
		pImpl(new Impl)
	{
		pImpl->m_Condition = condition;
		pImpl->m_Statement = stm;
		pImpl->m_ElsStatement = elsstm;
	}

	IfElsStm::~IfElsStm() {
		delete pImpl;

	}

	const Expression* IfElsStm::getCondition()const {
		return pImpl->m_Condition;
	}

	const Statement* IfElsStm::getStatement()const {
		return pImpl->m_Statement;
	}

	const Statement* IfElsStm::getElsStatement()const {
		return pImpl->m_ElsStatement;
	}

	SmtRes IfElsStm::Excute() const {
		setRuntimeLineNumber();
		auto val = getCondition()->Excute();
		if (val.getBool()) {
			return getStatement()->Excute();
		}
		else {
			return getElsStatement()->Excute();
		}
		return SmtRes();
	}



	//--------------------------------------------------------------------------------------
	///  while文クラス
	//--------------------------------------------------------------------------------------
	struct WhileStm::Impl {
		const Expression* m_Condition;
		const Statement* m_Statement;
	};

	WhileStm::WhileStm(const Expression* condition, const Statement* stm)
		: Statement(StatementType::whileStm),
		pImpl(new Impl)
	{
		pImpl->m_Condition = condition;
		pImpl->m_Statement = stm;
	}

	WhileStm::~WhileStm() {
		delete pImpl;
	}

	const Expression* WhileStm::getCondition()const {
		return pImpl->m_Condition;
	}

	const Statement* WhileStm::getStatement()const {
		return pImpl->m_Statement;
	}

	SmtRes WhileStm::Excute() const {
		setRuntimeLineNumber();
		Interpreter::getInp()->pushBreak();
		Interpreter::getInp()->pushLoop();
		while (getCondition()->Excute().getBool()) {
			auto res = getStatement()->Excute();
			if (res.m_Type == SmtResType::continueType) {
				continue;
			}
			else if (res.m_Type == SmtResType::breakType) {
				break;
			}
			else if (res.m_Type == SmtResType::returnTpe) {
				Interpreter::getInp()->popLoop();
				Interpreter::getInp()->popBreak();
				return res;
			}
		}
		Interpreter::getInp()->popLoop();
		Interpreter::getInp()->popBreak();
		return SmtRes();
	}
	//--------------------------------------------------------------------------------------
///  for文クラス
//--------------------------------------------------------------------------------------
	struct ForStm::Impl {
		const Statement* m_InitStatement;
		const Expression* m_Condition;
		const Expression* m_Post;
		const Statement* m_Statement;
	};

	ForStm::ForStm(const Statement* initstm, const Expression* condition, const Expression* post,
		const Statement* stm)
		: Statement(StatementType::forStm),
		pImpl(new Impl)
	{
		pImpl->m_InitStatement = initstm;
		pImpl->m_Condition = condition;
		pImpl->m_Post = post;
		pImpl->m_Statement = stm;
	}

	ForStm::~ForStm() {
		delete pImpl;

	}

	const Statement* ForStm::getInitStatement()const {
		return pImpl->m_InitStatement;
	}

	const Expression* ForStm::getCondition()const {
		return pImpl->m_Condition;
	}
	const Expression* ForStm::getPost()const {
		return pImpl->m_Post;
	}

	const Statement* ForStm::getStatement()const {
		return pImpl->m_Statement;
	}

	SmtRes ForStm::Excute() const {
		setRuntimeLineNumber();
		Interpreter::getInp()->pushBreak();
		Interpreter::getInp()->pushLoop();
		for (getInitStatement()->Excute();
			getCondition()->Excute().getBool();
			getPost()->Excute()) {
			auto res = getStatement()->Excute();
			if (res.m_Type == SmtResType::continueType) {
				continue;
			}
			else if (res.m_Type == SmtResType::breakType) {
				break;
			}
			else if (res.m_Type == SmtResType::returnTpe) {
				Interpreter::getInp()->popLoop();
				Interpreter::getInp()->popBreak();
				return res;
			}
		}
		Interpreter::getInp()->popLoop();
		Interpreter::getInp()->popBreak();
		return SmtRes();
	}

	//--------------------------------------------------------------------------------------
///  continue文クラス
//--------------------------------------------------------------------------------------
	ContinueStm::ContinueStm()
		: Statement(StatementType::breakStm)
	{
	}

	ContinueStm::~ContinueStm() {

	}

	SmtRes ContinueStm::Excute() const {
		setRuntimeLineNumber();
		if (Interpreter::getInp()->isContinueOK()) {
			SmtRes ret;
			ret.m_Type = SmtResType::continueType;
			return ret;
		}
		else {
			Interpreter::getInp()->runtimeExit(2018);
		}
		return SmtRes();
	}


	//--------------------------------------------------------------------------------------
///  break文クラス
//--------------------------------------------------------------------------------------

	BreakStm::BreakStm()
		: Statement(StatementType::breakStm)
	{
	}

	BreakStm::~BreakStm() {

	}

	SmtRes BreakStm::Excute() const {
		setRuntimeLineNumber();
		if (Interpreter::getInp()->isBreakOK()) {
			SmtRes ret;
			ret.m_Type = SmtResType::breakType;
			return ret;
		}
		else {
			Interpreter::getInp()->runtimeExit(2016);
		}
		return SmtRes();
	}

	//--------------------------------------------------------------------------------------
///  return文クラス
//--------------------------------------------------------------------------------------
	struct ReturnStm::Impl {
		const Expression* m_RetExpression;
	};

	ReturnStm::ReturnStm()
		: Statement(StatementType::returnStm),
		pImpl(new Impl)
	{
		pImpl->m_RetExpression = nullptr;
	}


	ReturnStm::ReturnStm(const Expression* retexp)
		: Statement(StatementType::returnStm),
		pImpl(new Impl)
	{
		pImpl->m_RetExpression = retexp;
	}

	ReturnStm::~ReturnStm() {
		delete pImpl;

	}

	const Expression* ReturnStm::getRetExp()const {
		return pImpl->m_RetExpression;
	}

	SmtRes ReturnStm::Excute() const {
		setRuntimeLineNumber();
		if (Interpreter::getInp()->isFunctionRuntime()) {
			if (getRetExp() == nullptr) {
				SmtRes ret;
				ret.m_RetValue = Value();
				ret.m_Type = SmtResType::returnTpe;
				return ret;
			}
			Value val = getRetExp()->Excute();
			SmtRes ret;
			ret.m_RetValue = val;
			ret.m_Type = SmtResType::returnTpe;
			return ret;
		}
		else {
			Interpreter::getInp()->runtimeExit(2017);
		}
		return SmtRes();
	}




	//--------------------------------------------------------------------------------------
///  ブロック文クラス
//--------------------------------------------------------------------------------------
	struct BlockStm::Impl {
		StatementList * m_StatementList;
	};

	BlockStm::BlockStm(StatementList* stml)
		: Statement(StatementType::blockStm),
		pImpl(new Impl)
	{
		pImpl->m_StatementList = stml;
	}

	BlockStm::BlockStm()
		: Statement(StatementType::blockStm),
		pImpl(new Impl)
	{
		pImpl->m_StatementList = nullptr;
	}

	BlockStm::~BlockStm() {}
	const StatementList* BlockStm::getStatementList()const {
		return pImpl->m_StatementList;
	}

	SmtRes BlockStm::Excute() const {
		setRuntimeLineNumber();
		Interpreter::getInp()->pushRuntime();
		if (auto stml = getStatementList()) {
			auto res = stml->Excute();
			Interpreter::getInp()->popRuntime();
			return res;
		}
		Interpreter::getInp()->popRuntime();
		return SmtRes();
	}

	//--------------------------------------------------------------------------------------
///  パラメータリストクラス
//--------------------------------------------------------------------------------------
	struct ParameterList::Impl {
		const char* m_Ident;
		ParameterList* m_Next;
	};

	ParameterList::ParameterList() :
		ObjBase(ObjType::ParamListType),
		pImpl(new Impl)
	{
		pImpl->m_Ident = nullptr;
		pImpl->m_Next = nullptr;
	}

	ParameterList::ParameterList(const char* ident) :
		ObjBase(ObjType::ParamListType),
		pImpl(new Impl)
	{
		pImpl->m_Ident = Interpreter::getInp()->createFixedString(ident);
		pImpl->m_Next = nullptr;
	}

	ParameterList::~ParameterList() {
		delete pImpl;
	}

	const char* ParameterList::getIdent() const {
		return pImpl->m_Ident;
	}

	ParameterList* ParameterList::getNext()const {
		return pImpl->m_Next;
	}

	void ParameterList::setNext(ParameterList* next) {
		pImpl->m_Next = next;
	}


	//--------------------------------------------------------------------------------------
	///  function定義クラス
	//--------------------------------------------------------------------------------------
	struct FunctionDefineStm::Impl {
		string m_Ident;
		const ParameterList* m_ParameterList;
		const Statement* m_Statement;
	};

	FunctionDefineStm::FunctionDefineStm(const char* ident, const ParameterList* pml, const Statement* stm)
		: Statement(StatementType::breakStm),
		pImpl(new Impl)
	{
		pImpl->m_Ident = ident;
		pImpl->m_ParameterList = pml;
		pImpl->m_Statement = stm;
	}

	FunctionDefineStm::~FunctionDefineStm() {
		delete pImpl;

	}

	const ParameterList* FunctionDefineStm::getParamList() const {
		return pImpl->m_ParameterList;
	}


	SmtRes FunctionDefineStm::Excute() const {
		setRuntimeLineNumber();
		if (Interpreter::getInp()->isFunctionRuntime()) {
			Interpreter::getInp()->runtimeExit(2014);
			return SmtRes();
		}
		Interpreter::getInp()->setFunctionRuntime(true);
		auto s = pImpl->m_Statement->Excute();
		Interpreter::getInp()->setFunctionRuntime(false);
		return s;
	}
	//--------------------------------------------------------------------------------------
	///  print文クラス
	//--------------------------------------------------------------------------------------
	struct PrintStm::Impl {
		const Expression* m_Expression;
		bool m_Nflg;
	};

	PrintStm::PrintStm(const Expression* target, bool nflg)
		: Statement(StatementType::printStm),
		pImpl(new Impl)
	{
		pImpl->m_Expression = target;
		pImpl->m_Nflg = nflg;
	}

	PrintStm::~PrintStm() {
		delete pImpl;
	}

	const Expression* PrintStm::getExpression()const {
		return pImpl->m_Expression;
	}

	bool PrintStm::getNflg() const {
		return pImpl->m_Nflg;
	}

	SmtRes PrintStm::Excute() const {
		setRuntimeLineNumber();
		auto val = pImpl->m_Expression->Excute();
		switch (val.getType()) {
		case ValueType::boolVal:
			cout << val.getBool();
			break;
		case ValueType::intVal:
			cout << val.getInt();
			break;
		case ValueType::doubleVal:
			cout << val.getDouble();
			break;
		case ValueType::stringVal:
			cout << val.getString();
			break;
		case ValueType::voidVal:
			cout << val.getString();
		}
		if (getNflg()) {
			cout << endl;
		}
		//void型を返す
		return SmtRes();
	}

}
//end namespace vv12