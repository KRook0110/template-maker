#ifndef STRINGUTIL_HPP
#define STRINGUTIL_HPP

#include <string>


namespace util {
std::string left_trim(const std::string& str);

std::string right_trim(const std::string& str);
std::string trim(const std::string& str);
}  // namespace util

#endif // STRINGUTIL_HPP
