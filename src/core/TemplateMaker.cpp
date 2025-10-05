
#include <CLI/CLI.hpp>
#include <iostream>

#include "../utils/PathUtil.hpp"
#include "TemplateMaker.hpp"

void copy_files(fs::path source, fs::path destination) {
    source = fs::absolute(util::expand_path(source));
    destination = fs::absolute(util::expand_path(destination));
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
        std::cout << "Successfully copied " << entry_path << std::endl;
    }
}

void apply_template(const TemplateMakerOptions& options) {
    // find the same directory names based on options.template_name

    fs::path source_path =
        fs::absolute(util::expand_path(options.template_path));
    fs::path destination = fs::absolute(util::expand_path(options.destination));

    for (const fs::directory_entry& entry :
         fs::directory_iterator{source_path}) {
        if (entry.path().filename() != options.template_name) continue;
        copy_files(entry.path(), destination);
        return;
    }
    std::cout << "Failed to find template" << std::endl;
}

