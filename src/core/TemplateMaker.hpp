#ifndef TEMPLATEMAKER_HPP
#define TEMPLATEMAKER_HPP

#include <string>

const std::string DEFAULT_TEMPLATE_PATH = "~/TemplateMaker/";
const std::string DEFAULT_DESTINATION = "./";

struct TemplateMakerOptions {
    std::string template_path = DEFAULT_TEMPLATE_PATH;
    std::string destination = DEFAULT_DESTINATION;
    std::string template_name;
    bool use_fzf;
};

void apply_template(const TemplateMakerOptions& options);


#endif // TEMPLATEMAKER_HPP
