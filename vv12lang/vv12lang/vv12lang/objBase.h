#pragma once

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  オブジェクトタイプ
	//--------------------------------------------------------------------------------------
	enum class ObjType {
		NullType,
		ExpType,
		StmType,
		StmListType,
		ParamListType,
		RootType,
		InterpreterType,
		objTypeCount
	};

	//--------------------------------------------------------------------------------------
	///  Objectベース（インターフェイス）
	//--------------------------------------------------------------------------------------
	class ObjBase {
	protected:
		ObjBase(ObjType type);
	public:
		virtual ~ObjBase();
		ObjType getObjType()const;
		int getLineNumber()const;
		void setRuntimeLineNumber()const;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

}
//end namespace vv12