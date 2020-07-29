
#include <iostream>
#include <string>
#include <utility>
#include <cstring>
#include <utils\binpack.h>
#include "Unpack.h"

using namespace std;
//��ӡ�ڴ�����

namespace cq::utils {
	//�ڴ淭ת
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

	//���ֽڼ�...
	//��ԭ�е����ݻ����ϲ���
	template <typename ClassType>
	unsigned char* toBin(ClassType& i)
	{
		return Flip(reinterpret_cast<unsigned char*>(&i), sizeof(ClassType));
	}
}