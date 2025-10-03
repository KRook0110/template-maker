#include <CLI/CLI.hpp>
#include <cstdlib>
#include <filesystem>
#include <iostream>

const std::string DEFAULT_TEMPLATE_PATH = "~/TemplateMaker/";
const std::string DEFAULT_DESTINATION = "./";

namespace fs = std::filesystem;

namespace path_util {
fs::path expand_path(fs::path path) {
    std::string str_path = path.string();
    if (str_path.empty() || str_path.front() != '~') return path;
    std::string home = getenv("HOME");
    home += str_path.substr(1, str_path.size() - 1);
    return fs::path(home);
}
}  // namespace path_util

struct TemplateMakerOptions {
    std::string template_path = DEFAULT_TEMPLATE_PATH;
    std::string destination = DEFAULT_DESTINATION;
    std::string template_name;
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
        } catch(fs::filesystem_error err)  {
            std::cout << "Failed to copy " << entry_path << std::endl;
            std::cout << "Reason : " << err.what() << std::endl;

            continue;
        }
        std::cout << "Successfully coppied " << entry_path << std::endl;
    }
}

void apply_template(TemplateMakerOptions options) {

}
void setup_cli_options(int argc, const char** argv,
                       TemplateMakerOptions& options, CLI::App& app) {
    // TODO: Decide should I move this shit out

    app.add_option("template-name,-t,--template-name", options.template_name,
                   "which template you want to use")
    ->required();

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

    copy_files(options.template_path, options.destination);
    return 0;
}
