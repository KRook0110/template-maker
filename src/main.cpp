#include <CLI/CLI.hpp>
#include <array>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <iostream>

const std::string DEFAULT_TEMPLATE_PATH = "~/TemplateMaker/";
const std::string DEFAULT_DESTINATION = "./";

namespace fs = std::filesystem;
namespace cmdline_util {
std::string exec(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed");
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    return result;
}
}  // namespace cmdline_util

namespace path_util {
fs::path expand_path(fs::path path) {
    std::string str_path = path.string();
    if (str_path.empty() || str_path.front() != '~') return path;
    std::string home = getenv("HOME");
    home += str_path.substr(1, str_path.size() - 1);
    return fs::path(home);
}
}  // namespace path_util
namespace string_util {
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
}  // namespace string_util

struct TemplateMakerOptions {
    std::string template_path = DEFAULT_TEMPLATE_PATH;
    std::string destination = DEFAULT_DESTINATION;
    std::string template_name;
    bool use_fzf;
};

void copy_files(fs::path source, fs::path destination) {
    source = fs::absolute(path_util::expand_path(source));
    destination = fs::absolute(path_util::expand_path(destination));
    const fs::copy_options options =
        fs::copy_options::overwrite_existing | fs::copy_options::recursive;
    for (const fs::directory_entry& entry : fs::directory_iterator(source)) {
        fs::path entry_path = entry.path();
        try {
            fs::copy(entry_path, destination / entry_path.filename(), options);
        } catch (fs::filesystem_error err) {
            std::cout << "Failed to copy " << entry_path << std::endl;
            std::cout << "Reason : " << err.what() << std::endl;

            continue;
        }
        std::cout << "Successfully coppied " << entry_path << std::endl;
    }
}

void apply_template(TemplateMakerOptions options) {
    // find the same directory names based on options.template_name

    fs::path source_path =
        fs::absolute(path_util::expand_path(options.template_path));
    fs::path destination =
        fs::absolute(path_util::expand_path(options.destination));

    for (const fs::directory_entry& entry :
         fs::directory_iterator{source_path}) {
        if (entry.path().filename() != options.template_name) continue;
        copy_files(entry.path(), destination);
        return;
    }
    std::cout << "Failed to find template" << std::endl;
}

void setup_cli_options(int argc, const char** argv,
                       TemplateMakerOptions& options, CLI::App& app) {
    // TODO: Decide should I move this shit out

    app.add_option("template-name,-t,--template-name", options.template_name,
                   "which template you want to use");

    app.add_flag("--fzf", options.use_fzf);

    app.add_option("-s,--source", options.template_path,
                   "defines the source of the templates")
        ->check(CLI::ExistingPath);

    app.add_option("-d,--destination", options.destination,
                   "define where you want the template to be created")
        ->check(CLI::ExistingPath);

    // TODO: Decide should I move this shit out aswell?
}

int main(int argc, const char** argv) {
    std::cout << "TemplateMaker has started" << std::endl;
    TemplateMakerOptions options;
    CLI::App app{"TemplateMaker"};
    setup_cli_options(argc, argv, options, app);
    CLI11_PARSE(app, argc, argv);

    if (options.use_fzf) {
        options.template_name =
            cmdline_util::exec("fd --type directory -d 1 --base-directory " +
                               options.template_path + " | fzf");
        if(options.template_name.back() == '/') options.template_name.pop_back();
        std::cout << "template name = " << options.template_name << "."
                  << std::endl;
    }

    if (options.template_name.empty()) {
        std::cout
            << "please input a template name or add --fzf to find a template"
            << std::endl;
        return 1;
    }

    options.template_name = string_util::right_trim(options.template_name);

    apply_template(options);

    return 0;
}
