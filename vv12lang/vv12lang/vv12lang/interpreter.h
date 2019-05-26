#pragma once

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  ���[�g�N���X
	//--------------------------------------------------------------------------------------
	class Root : public StmExBase {
	public:
		Root(const StatementList* stml);
		virtual ~Root();
		virtual SmtRes Excute() const  override;
		const StatementList* getStmeList()const;
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

	//--------------------------------------------------------------------------------------
	///  �C���^�[�v���^�N���X
	//--------------------------------------------------------------------------------------
	class Interpreter : public ObjBase {
		Interpreter();
	public:
		virtual ~Interpreter();
		int Compile(FILE *fp);
		void Exec() const;
		void Delete();
		///Util
		void setConfig(const char* key, const Value val);
		Value getConfig(const char* key);
		void pushBackObject(ObjBase* pobj);
		const char* createFixedString(const char* ext);
		///Expression
		Expression* createVariableExp(const char* ident);
		Expression* createIntLiteralExp(const char* ext);
		Expression* createDoubleLiteralExp(const char* ext);
		Expression* createBinaryExp(const Expression* left, const Expression* right, ExpressionType t);
		Expression* createAssExp(const Expression* ident, const Expression* right);
		Expression* createToAssExp(const Expression* ident, const Expression* right, ExpressionType t);

		//�����񃊃e����
		void startStringLiteral();
		void addStringLiteral(char ext);
		Expression* createStringLiteralExp();

		///Statement
		//Util template
		template<typename T, typename... Ts>
		Statement* createStatement(Ts&&... params) {
			auto ptr = new T(params...);
			pushBackObject(ptr);
			return ptr;
		}
		///StatementList
		StatementList* createStatementList(const Statement* stm);
		StatementList* createStatementList(StatementList* stml, const Statement* stm);
		//Root
		Root*  createRoot(const StatementList* stml);
		//�C���X�^���X�Q��
		static Interpreter* getInp();
		///Exec�֘A
		///�ϐ��̒l�̎Q�Ƃ��擾
		Value& getGlobalValiableValue(const char* key);
		///�P�K�w�����^�C����push����
		void pushRuntime(bool IsFunc = false);
		///�P�K�w�����^�C����pop����
		void popRuntime();

		//���[�v���s�����ǂ���
		void pushLoop();
		void popLoop();
		//break�\�Ȑ[����push����B
		void pushBreak();
		//break�\�Ȑ[����pop����B
		void popBreak();


		///�V���^�b�N�X�G���[�\���֘A
		void syntaxKeepExit(int mess_id, const char* detail);
		///�V���^�b�N�X�G���[(�s�ԍ��A�ʒu���t��)
		void syntaxExit(int mess_id, int linnum, const char* detail, bool bison = true);
		///�����^�C�����̍s�ԍ�
		void setRuntimeLineNumber(int num);
		int getRuntimeLineNumber() const;
		///�����^�C���G���[(�s�ԍ��t��)
		void runtimeExit(int mess_id, const char* target = nullptr);
		///�����^�C�����[�j���O
		void runtimeWorning(int mess_id);
		///�x�����o�����ǂ���
		bool isWorningOut() const;
		void setWorningOut(bool b);
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		Impl* pImpl;
	};

}
//end namespace vv12