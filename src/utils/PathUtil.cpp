#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace util {
fs::path expand_path(fs::path path) {
    std::string str_path = path.string();
    if (str_path.empty() || str_path.front() != '~') return path;
    std::string home = getenv("HOME");
    home += str_path.substr(1, str_path.size() - 1);
    return fs::path(home);
}
}  // namespace path_util
