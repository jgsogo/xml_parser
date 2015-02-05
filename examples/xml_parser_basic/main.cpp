
#include "stdafx.h"

#include <iostream>
#include "../../xml_parser/parser_expat.h"

int main() {
    core::service::expat::parser_expat parser;

    std::function<void (const core::service::node& node)> f = [&](const core::service::node& node) {
        std::size_t depth = node.get_depth();
        std::string indent; indent.assign(depth, ' ');

        std::cout << "\n" << indent << "<" << node.get_tag() << ">" << std::endl;
        auto attribs = node.get_attributes();
        for (auto it = attribs.begin(); it != attribs.end(); ++it) {
            std::cout << indent << "\t" << it->first << ": " << it->second << std::endl;
            }
        if (node.has_data()) {
            std::cout << indent << "\tDATA: " << node.get_data() << std::endl;
            }
        auto children = node.get_children();
        for (auto it = children.begin(); it != children.end(); ++it) {
            f(**it);
            }
        };

    parser.register_tag("titl", f);
    parser.register_tag("producer", f);
    parser.register_tag("var", f);
    
    parser.parse_file("nes96.xml", "codeBook", [](const std::string& msg) { std::cout << "status: " << msg << std::endl;});
                    
    return 0;
    }