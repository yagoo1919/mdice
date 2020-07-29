#include "base64.h"
namespace cq::utils::base64 {
	std::string encode(const std::string& bytes)
	{
		return base64_encode(bytes);
	};
	std::string decode(const std::string& str)
	{
		return base64_decode(str);
	};
	std::string& msg_encode(std::string& s, const bool isCQ)
	{
		msg_replace(s, "&", "&amp;");
		msg_replace(s, "[", "&#91;");
		msg_replace(s, "]", "&#93;");
		msg_replace(s, "\t", "&#44;");
		if (isCQ)
			msg_replace(s, ",", "&#44;");
		return s;
	}

	std::string& msg_decode(std::string& s, const bool isCQ)
	{
		if (isCQ)
			msg_replace(s, "&#44;", ",");
		msg_replace(s, "&#91;", "[");
		msg_replace(s, "&#93;", "]");
		msg_replace(s, "&#44;", "\t");
		msg_replace(s, "&amp;", "&");
		return s;
	}
	
} 