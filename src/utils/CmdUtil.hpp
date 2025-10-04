#ifndef CMDUTIL_HPP
#define CMDUTIL_HPP

#include <string>

namespace util {
/**
 * @brief Executes a shell command and returns its output as a string.
 *
 * @param command The command string to execute.
 * @return std::string The captured output of the command.
 * @throws std::runtime_error if popen() fails.
 */
std::string exec(const std::string& command);
}  // namespace util

#endif  // CMDUTIL_HPP
