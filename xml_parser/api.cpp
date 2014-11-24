
#include "stdafx.h"
#include <cstring>
#include "api.h"

#include "xml_parser/config.h"
#include "parser_expat.h"

void get_version(std::string& xml_parser_version) {
	xml_parser_version = XML_PARSER_VERSION_STRING;
	}

int build_xml_parser(core::service::parser* &parser, const std::string& parser_technology) {
	if (std::strcmp(parser_technology.c_str(), "expat")==0) {
		parser = new core::service::expat::parser_expat();
		return 0;
		}
	else {
		LOG_ERROR("Parser technology '" << parser_technology << "' not recognized.");
		return -1;
		}
	}

int delete_xml_parser(core::service::parser* parser) {
    delete parser;
    return 0;
    }
