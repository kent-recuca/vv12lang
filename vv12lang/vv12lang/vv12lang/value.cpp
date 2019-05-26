#include <cstdlib>
#include <cmath>
#include <cfenv>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include <typeinfo>
#include "util.h"
#include "proc.h"
using namespace std;

namespace vv12 {

	//--------------------------------------------------------------------------------------
	///  暗黙の型キャスト
	//--------------------------------------------------------------------------------------
	inline bool toBoolValue() {
		return false;
	}
	inline bool toBoolValue(bool b) {
		return b;
	}
	inline bool toBoolValue(int i) {
		if (i != 0) {
			return true;
		}
		else {
			return false;
		}
	}
	inline bool toBoolValue(double b) {
		if (b != 0.0) {
			return true;
		}
		else {
			return false;
		}
	}
	inline bool toBoolValue(const string& str) {
		//必ず10進数に変換
		int i;
		try {
			i = std::stoi(str, nullptr, 10);
		}
		catch (...) {
			i = 0;
		}
		if (i != 0) {
			return true;
		}
		else {
			return false;
		}
	}

	inline int toIntValue() {
		return 0;
	}

	inline int toIntValue(bool b) {
		if (b != false) {
			return 1;
		}
		else {
			return 0;
		}
	}

	inline int toIntValue(int i) {
		return i;
	}

	inline int toIntValue(double d) {
		//強制的な型返還
		int i = (int)d;
		return i;
	}

	inline int toIntValue(const string& str) {
		//必ず10進数に変換
		int i;
		try {
			i = std::stoi(str, nullptr, 10);
		}
		catch (...) {
			i = 0;
		}
		return i;
	}

	inline double toDoubleValue() {
		return 0.0;
	}

	inline double toDoubleValue(bool b) {
		if (b) {
			return 1.0;
		}
		else {
			return 0.0;
		}
	}

	inline double toDoubleValue(int i) {
		//C++に合わせた型返還
		double d = i;
		return d;
	}

	inline double toDoubleValue(double d) {
		return d;
	}

	inline double toDoubleValue(const string& str) {
		//10進のdoubleに変換
		double d;
		try {
			d = std::stod(str);
		}
		catch (...) {
			d = 0.0;
		}
		return d;
	}

	inline string toStringValue() {
		return string("");
	}

	inline string toStringValue(bool b) {
		if (b) {
			return string("1");
		}
		else {
			return string("");
		}
	}

	inline string toStringValue(int i) {
		string str = std::to_string(i);
		return str;
	}

	inline string toStringValue(double d) {
		string str = std::to_string(d);
		return str;
	}

	inline string toStringValue(const string& str) {
		return str;
	}


	//--------------------------------------------------------------------------------------
	///  配列
	//--------------------------------------------------------------------------------------
	struct ArrItem {
		size_t sztKey;
		string strKey;
		bool isKeyStr;
		Value val;
		ArrItem() :
			sztKey(0), strKey(), isKeyStr(false)
		{}
	};

	//--------------------------------------------------------------------------------------
	///  値
	//--------------------------------------------------------------------------------------
	struct Value::Impl {
		ValueType m_Type;
		string strV;
		vector<shared_ptr<ArrItem>> arrV;
		//get用のstring
		string tmpStr;
		union {
			bool boolV;
			int intV;
			double doubleV;
		};
	};

	Value::Value() :
		pImpl(new Impl)
	{
		pImpl->m_Type = ValueType::voidVal;
		pImpl->intV = 0;
	}

	Value::Value(bool b) :
		pImpl(new Impl)
	{
		pImpl->m_Type = ValueType::boolVal;
		pImpl->boolV = b;
	}

	Value::Value(int i) :
		pImpl(new Impl)
	{
		pImpl->m_Type = ValueType::intVal;
		pImpl->intV = i;
	}

	Value::Value(double d) :
		pImpl(new Impl)
	{
		pImpl->m_Type = ValueType::doubleVal;
		pImpl->doubleV = d;
	}

	Value::Value(const char* s) :
		pImpl(new Impl)
	{
		pImpl->m_Type = ValueType::stringVal;
		pImpl->strV = s;
	}

	Value::Value(const Value& other) :
		pImpl(new Impl)
	{
		*pImpl = *(other.pImpl);
	}

	Value& Value::operator=(bool b) {
		pImpl->arrV.clear();
		pImpl->m_Type = ValueType::boolVal;
		pImpl->boolV = b;
		pImpl->strV = "";
		pImpl->tmpStr = "";
		return *this;
	}

	Value& Value::operator=(int i) {
		pImpl->arrV.clear();
		pImpl->m_Type = ValueType::intVal;
		pImpl->intV = i;
		pImpl->strV = "";
		pImpl->tmpStr = "";
		return *this;
	}

	Value& Value::operator=(double d) {
		pImpl->arrV.clear();
		pImpl->m_Type = ValueType::doubleVal;
		pImpl->doubleV = d;
		pImpl->strV = "";
		pImpl->tmpStr = "";
		return *this;
	}

	Value& Value::operator=(const char* s) {
		pImpl->arrV.clear();
		pImpl->m_Type = ValueType::stringVal;
		pImpl->intV = 0;
		pImpl->strV = s;
		pImpl->tmpStr = "";
		return *this;
	}

	Value& Value::operator=(const Value& other) {
		*pImpl = *(other.pImpl);
		return *this;
	}

	Value::~Value() {
		delete pImpl;
		pImpl = nullptr;
	}

	ValueType Value::getType() const {
		return pImpl->m_Type;
	}

	bool Value::getBool() const {
		switch (getType())
		{
		case ValueType::boolVal:
			return pImpl->boolV;
			break;
		case ValueType::intVal:
			return toBoolValue(pImpl->intV);
			break;
		case ValueType::doubleVal:
			return toBoolValue(pImpl->doubleV);
			break;
		case ValueType::stringVal:
			return toBoolValue(pImpl->strV);
			break;
		case ValueType::arrayVal:
			Interpreter::getInp()->runtimeExit(2021);
			break;
		}
		return toBoolValue();
	}

	int Value::getInt() const {
		switch (getType()) {
		case ValueType::boolVal:
			return toIntValue(pImpl->boolV);
			break;
		case ValueType::intVal:
			return pImpl->intV;
			break;
		case ValueType::doubleVal:
			return toIntValue(pImpl->doubleV);
			break;
		case ValueType::stringVal:
			return toIntValue(pImpl->strV);
			break;
		case ValueType::arrayVal:
			Interpreter::getInp()->runtimeExit(2021);
			break;
		}
		return toIntValue();
	}

	double Value::getDouble() const {
		switch (getType()) {
		case ValueType::boolVal:
			return toDoubleValue(pImpl->boolV);
			break;
		case ValueType::intVal:
			return toDoubleValue(pImpl->intV);
			break;
		case ValueType::doubleVal:
			return pImpl->doubleV;
			break;
		case ValueType::stringVal:
			return toDoubleValue(pImpl->strV);
			break;
		case ValueType::arrayVal:
			Interpreter::getInp()->runtimeExit(2021);
			break;
		}
		return toDoubleValue();
	}

	const char* Value::getString() const {
		switch (getType()) {
		case ValueType::boolVal:
			pImpl->tmpStr = toStringValue(pImpl->boolV);
			break;
		case ValueType::intVal:
			pImpl->tmpStr = toStringValue(pImpl->intV);
			break;
		case ValueType::doubleVal:
			pImpl->tmpStr = toStringValue(pImpl->doubleV);
			break;
		case ValueType::stringVal:
			pImpl->tmpStr = pImpl->strV;
			break;
		case ValueType::arrayVal:
			Interpreter::getInp()->runtimeExit(2021);
			break;
		default:
			pImpl->tmpStr = toStringValue();
			break;
		}
		return pImpl->tmpStr.c_str();
	}

	Value Value::getTypedValue(ValueType t) const {
		Value val;
		switch (t) {
		case ValueType::boolVal:
			val = getBool();
			break;
		case ValueType::intVal:
			val = getInt();
			break;
		case ValueType::doubleVal:
			val = getDouble();
			break;
		case ValueType::stringVal:
			val = getString();
			break;
		case ValueType::arrayVal:
			Interpreter::getInp()->runtimeExit(2021);
			break;
		default:
			break;
		}
		return val;
	}


	Value getOptimalTypeValue(double ret) {
		double mod = std::fmod(ret, 1.0);
		Value eps = Interpreter::getInp()->getConfig("calc_epsilon");
		double epsd = eps.getDouble();
		if (abs(epsd) >= 0.1)epsd = 0.1;
		if (std::fabs(mod) <= epsd) {
			return Value((int)ret);
		}
		return Value(ret);
	}

	Value Value::operator+(const Value& other) {
		double ret((*this).getDouble());
		ret += other.getDouble();
		return getOptimalTypeValue(ret);
	}

	Value Value::operator-(const Value& other) {
		double ret((*this).getDouble());
		ret -= other.getDouble();
		return getOptimalTypeValue(ret);
	}

	Value Value::operator*(const Value& other) {
		double ret((*this).getDouble());
		ret *= other.getDouble();
		return getOptimalTypeValue(ret);
	}

	Value Value::operator/(const Value& other) {
		double other_double = other.getDouble();
		if (other_double == 0.0) {
			Interpreter::getInp()->runtimeExit(2003);
		}
		double ret((*this).getDouble());
		ret /= other_double;
		return getOptimalTypeValue(ret);
	}

	Value Value::operator%(const Value& other) {
		double other_double = other.getDouble();
		if (other_double == 0.0) {
			Interpreter::getInp()->runtimeExit(2003);
		}
		double ret((*this).getDouble());
		ret = fmod(ret, other_double);
		return getOptimalTypeValue(ret);
	}


	Value Value::operator&(const Value& other) {
		string ret((*this).getString());
		ret += other.getString();
		return Value(ret.c_str());
	}

	Value&  Value::operator&=(const Value& other) {
		*this = *this & other;
		return *this;
	}

	Value& Value::operator+=(const Value& other) {
		*this = *this + other;
		return *this;
	}

	Value& Value::operator-=(const Value& other) {
		*this = *this - other;
		return *this;

	}

	Value& Value::operator*=(const Value& other) {
		*this = *this * other;
		return *this;
	}

	Value& Value::operator/=(const Value& other) {
		*this = *this / other;
		return *this;
	}

	bool  Value::operator == (const Value& other) {
		if (this->getType() == ValueType::stringVal
			&& other.getType() == ValueType::stringVal) {
			return (pImpl->strV == other.pImpl->strV);
		}
		if (this->getType() == ValueType::doubleVal
			|| other.getType() == ValueType::doubleVal) {
			double left((*this).getDouble());
			double right(other.getDouble());
			return (left == right);
		}
		else if (this->getType() == ValueType::intVal
			|| other.getType() == ValueType::intVal) {
			int left((*this).getInt());
			int right(other.getInt());
			return (left == right);
		}
		else if (this->getType() == ValueType::boolVal
			|| other.getType() == ValueType::boolVal) {
			bool left((*this).getBool());
			bool right(other.getBool());
			return (left == right);
		}
		else {
			return false;
		}
	}

	bool  Value::operator != (const Value& other) {
		return !((*this) == other);
	}

	bool Value::operator < (const Value& other) {
		double left((*this).getDouble());
		double right(other.getDouble());
		return (left < right);
	}

	bool Value::operator > (const Value& other) {
		double left((*this).getDouble());
		double right(other.getDouble());
		return (left > right);
	}

	bool Value::operator <= (const Value& other) {
		double left((*this).getDouble());
		double right(other.getDouble());
		return (left <= right);
	}

	bool Value::operator >= (const Value& other) {
		double left((*this).getDouble());
		double right(other.getDouble());
		return (left >= right);
	}

	bool Value::operator && (const Value& other) {
		bool left((*this).getBool());
		bool right(other.getBool());
		return (left && right);
	}

	bool Value::operator || (const Value& other) {
		bool left((*this).getBool());
		bool right(other.getBool());
		return (left || right);
	}

	void Value::setArrClear() {
		pImpl->arrV.clear();
		pImpl->m_Type = ValueType::arrayVal;
	}

	bool Value::isArrKey(size_t index)const {
		if (pImpl->m_Type != ValueType::arrayVal) {
			return false;
		}
		for (auto& v : pImpl->arrV) {
			if (v->isKeyStr == false && v->sztKey == index) {
				return true;
			}
		}
		return false;
	}

	bool Value::isArrKey(const char* key)const {
		if (pImpl->m_Type != ValueType::arrayVal) {
			return false;
		}
		for (auto& v : pImpl->arrV) {
			if (v->isKeyStr && v->strKey == key) {
				return true;
			}
		}
		return false;
	}

	void Value::createArrKey(size_t index) {
		pImpl->m_Type = ValueType::arrayVal;
		auto ptrArrItem = make_shared<ArrItem>();
		ptrArrItem->isKeyStr = false;
		ptrArrItem->sztKey = index;
		ptrArrItem->val = Value();
		size_t size = pImpl->arrV.size();
		pImpl->arrV.push_back(ptrArrItem);
	}

	void Value::createArrKey(const char* key) {
		pImpl->m_Type = ValueType::arrayVal;
		auto ptrArrItem = make_shared<ArrItem>();
		ptrArrItem->isKeyStr = true;
		ptrArrItem->strKey = key;
		ptrArrItem->val = Value("");
		size_t size = pImpl->arrV.size();
		pImpl->arrV.push_back(ptrArrItem);
	}

	size_t Value::getNextIndexKey() const {
		int lastIndex = -1;
		for (auto& v : pImpl->arrV) {
			if (v->isKeyStr == false) {
				if (((int)v->sztKey) > lastIndex) {
					lastIndex = (int)v->sztKey;
				}
			}
		}
		return (size_t)(lastIndex + 1);
	}



	const Value& Value::operator[](size_t index)const {
		for (auto& v : pImpl->arrV) {
			if (v->isKeyStr == false && v->sztKey == index) {
				return v->val;
			}
		}
		//無かった
		//ワーニングを出す
		Interpreter::getInp()->runtimeWorning(2022);
		auto ptrArrItem = make_shared<ArrItem>();
		ptrArrItem->isKeyStr = false;
		ptrArrItem->sztKey = index;
		ptrArrItem->val = Value();
		size_t size = pImpl->arrV.size();
		pImpl->m_Type = ValueType::arrayVal;
		pImpl->arrV.push_back(ptrArrItem);
		return pImpl->arrV[size]->val;
	}
	Value& Value::operator[](size_t index) {
		for (auto& v : pImpl->arrV) {
			if (v->isKeyStr == false && v->sztKey == index) {
				return v->val;
			}
		}
		//無かった
		auto ptrArrItem = make_shared<ArrItem>();
		ptrArrItem->isKeyStr = false;
		ptrArrItem->sztKey = index;
		ptrArrItem->val = Value();
		size_t size = pImpl->arrV.size();
		pImpl->m_Type = ValueType::arrayVal;
		pImpl->arrV.push_back(ptrArrItem);
		return pImpl->arrV[size]->val;
	}

	const Value& Value::operator[](const char* key)const {
		for (auto& v : pImpl->arrV) {
			if (v->isKeyStr && v->strKey == key) {
				return v->val;
			}
		}
		//無かった
		//ワーニングを出す
		Interpreter::getInp()->runtimeWorning(2022);
		auto ptrArrItem = make_shared<ArrItem>();
		ptrArrItem->isKeyStr = true;
		ptrArrItem->strKey = key;
		ptrArrItem->val = Value("");
		size_t size = pImpl->arrV.size();
		pImpl->m_Type = ValueType::arrayVal;
		pImpl->arrV.push_back(ptrArrItem);
		return pImpl->arrV[size]->val;

	}
	Value& Value::operator[](const char* key) {
		for (auto& v : pImpl->arrV) {
			if (v->isKeyStr && v->strKey == key) {
				return v->val;
			}
		}
		//無かった
		auto ptrArrItem = make_shared<ArrItem>();
		ptrArrItem->isKeyStr = true;
		ptrArrItem->strKey = key;
		ptrArrItem->val = Value("");
		size_t size = pImpl->arrV.size();
		pImpl->m_Type = ValueType::arrayVal;
		pImpl->arrV.push_back(ptrArrItem);
		return pImpl->arrV[size]->val;
	}

	size_t Value::getArrCount() const {
		return pImpl->arrV.size();
	}

	const Value& Value::getArrVValue(size_t index) const {
		return pImpl->arrV[index]->val;
	}
	Value& Value::getArrVValue(size_t index) {
		return pImpl->arrV[index]->val;
	}

	Value Value::getArrVKey(size_t index) const {
		Value ret;
		if (pImpl->arrV[index]->isKeyStr) {
			ret = pImpl->arrV[index]->strKey.c_str();
		}
		else {
			ret = (int)pImpl->arrV[index]->sztKey;
		}
		return ret;
	}

}
//end namespace vv12