#include <string>

#include "StringUtil.hpp"
namespace util {
std::string left_trim(const std::string& str) {
    int i = 0;
    while (i < str.size() && std::isspace(str[i])) i++;
    return str.substr(i, str.size() - i);
}
std::string right_trim(const std::string& str) {
    int i = str.size() - 1;
    while (i >= 0 && std::isspace(str[i])) i--;
    return str.substr(0, i + 1);
}
std::string trim(const std::string& str) { return left_trim(right_trim(str)); }

}  // namespace util
