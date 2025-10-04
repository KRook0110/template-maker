#include <CLI/CLI.hpp>
#include <cctype>
#include <cstdlib>
#include <iostream>

#include "core/TemplateMaker.hpp"
#include "utils/CmdUtil.hpp"
#include "utils/StringUtil.hpp"

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
        options.template_name = util::right_trim(
            util::exec("fd --type directory -d 1 --base-directory " +
                       options.template_path + " | fzf"));
        if (options.template_name.back() == '/')
            options.template_name.pop_back();
        std::cout << "Selected template " << options.template_name << "."
                  << std::endl;
    }

    if (options.template_name.empty()) {
        std::cout
            << "please input a template name or add --fzf to find a template"
            << std::endl;
        return 1;
    }

    options.template_name = util::right_trim(options.template_name);

    apply_template(options);

    return 0;
}
