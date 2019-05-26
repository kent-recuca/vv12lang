#pragma once

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  値タイプ
	//--------------------------------------------------------------------------------------
	enum class ValueType {
		boolVal = 0,
		intVal,
		doubleVal,
		stringVal,
		arrayVal,
		voidVal,
		countVal
	};


	//--------------------------------------------------------------------------------------
	///  値
	//--------------------------------------------------------------------------------------
	class Value {
	public:
		explicit Value();
		explicit Value(bool b);
		explicit Value(int i);
		explicit Value(double d);
		explicit Value(const char* s);
		Value(const Value& other);
		virtual ~Value();
		ValueType getType() const;
		bool getBool() const;
		int getInt() const;
		double getDouble() const;
		const char* getString() const;
		Value getTypedValue(ValueType t) const;
		Value& operator=(bool b);
		Value& operator=(int i);
		Value& operator=(double d);
		Value& operator=(const char* s);
		Value& operator=(const Value& other);
		Value operator+(const Value& other);
		Value operator-(const Value& other);
		Value operator*(const Value& other);
		Value operator/(const Value& other);
		Value operator%(const Value& other);
		Value operator&(const Value& other);
		Value& operator+=(const Value& other);
		Value& operator-=(const Value& other);
		Value& operator*=(const Value& other);
		Value& operator/=(const Value& other);
		Value& operator&=(const Value& other);
		bool operator == (const Value& other);
		bool operator != (const Value& other);
		bool operator < (const Value& other);
		bool operator > (const Value& other);
		bool operator <= (const Value& other);
		bool operator >= (const Value& other);
		bool operator && (const Value& other);
		bool operator || (const Value& other);
		//配列用
		void setArrClear();
		bool isArrKey(size_t index)const;
		bool isArrKey(const char* key)const;
		void createArrKey(size_t index);
		void createArrKey(const char* key);
		size_t getNextIndexKey() const;
		const Value& operator[](size_t index)const;
		Value& operator[](size_t index);
		const Value& operator[](const char* key)const;
		Value& operator[](const char* key);
		size_t getArrCount() const;
		const Value& getArrVValue(size_t index) const;
		Value& getArrVValue(size_t index);
		Value getArrVKey(size_t index) const;
	private:
		// pImplイディオム
		struct Impl;
		Impl* pImpl;
	};

}
//end namespace vv12