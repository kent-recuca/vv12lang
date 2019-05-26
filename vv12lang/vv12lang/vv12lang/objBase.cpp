#include "util.h"
#include "proc.h"

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  Objectベース（インターフェイス）
	//--------------------------------------------------------------------------------------
	struct ObjBase::Impl {
		ObjType m_ObjType;
		int m_LineNumber;
	};
	ObjBase::ObjBase(ObjType type) :
		pImpl(new Impl)
	{
		extern int gLine;
		pImpl->m_ObjType = type;
		pImpl->m_LineNumber = gLine;
	}
	ObjBase::~ObjBase() {}

	ObjType ObjBase::getObjType()const {
		return pImpl->m_ObjType;
	}

	int ObjBase::getLineNumber()const {
		return pImpl->m_LineNumber;
	}

	void ObjBase::setRuntimeLineNumber()const {
		Interpreter::getInp()->setRuntimeLineNumber(pImpl->m_LineNumber);
	}

}
// end namespace vv12