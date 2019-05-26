#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <memory>
using namespace std;

namespace vv12 {

#define vv12_MAX_TOKEN_LEN 255

	///string‚ð255•¶Žš‚ÉØ‚è‹l‚ß‚é
	inline string clampToken(const char* ext) {
		string str(ext);
		if (str.size() > vv12_MAX_TOKEN_LEN) {
			str.erase(vv12_MAX_TOKEN_LEN);
		}
		return str;
	}

}
//end namespace vv12