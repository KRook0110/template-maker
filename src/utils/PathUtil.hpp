#ifndef PATHUTIL_HPP
#define PATHUTIL_HPP

#include <filesystem>

namespace fs = std::filesystem;

namespace util {
/**
 * @brief Expands the '~' character in a path to the user's home directory.
 * * @param path The filesystem path object.
 * @return fs::path The expanded path.
 */
fs::path expand_path(fs::path path);
}  // namespace util

#endif  // PATHUTIL_HPP
