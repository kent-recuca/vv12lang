#pragma once

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  �I�u�W�F�N�g�^�C�v
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
	///  Object�x�[�X�i�C���^�[�t�F�C�X�j
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
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

}
//end namespace vv12