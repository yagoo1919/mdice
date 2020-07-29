#pragma once

#include "../common.h"

namespace cq::utils::base64 {
	extern std::string encode(const std::string& bytes);
    extern std::string decode(const std::string &str);
	extern std::string& msg_encode(std::string& s, bool isCQ = false);
	extern std::string& msg_decode(std::string& s, bool isCQ = false);
} // namespace cq::utils::base64
