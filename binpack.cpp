
#include <iostream>
#include <string>
#include <utility>
#include <cstring>
#include <utils\binpack.h>
#include "Unpack.h"

using namespace std;
//打印内存数据

namespace cq::utils {
	//内存翻转
	unsigned char* Flip(unsigned char* const str, int len)
	{
		auto f = 0;
		--len;
		while (f < len)
		{
			const auto p = str[len];
			str[len] = str[f];
			str[f] = p;
			++f;
			--len;
		}
		return str;
	}

	//到字节集...
	//在原有的数据基础上操作
	template <typename ClassType>
	unsigned char* toBin(ClassType& i)
	{
		return Flip(reinterpret_cast<unsigned char*>(&i), sizeof(ClassType));
	}
}