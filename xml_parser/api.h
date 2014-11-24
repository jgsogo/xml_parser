
#pragma once

#include "parser.h"
#include "node.h"

//! Build a parser using specified technology
extern "C" XML_PARSER_EXPORT void get_version(std::string& xml_parser_version);
extern "C" XML_PARSER_EXPORT int build_xml_parser(core::service::parser* &parser, const std::string& parser_technology = "expat");
extern "C" XML_PARSER_EXPORT int delete_xml_parser(core::service::parser* parser);