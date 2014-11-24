
#include "stdafx.h"

#include "node.h"
#include "expat_handler.h"

#include "node_expat.h"

#include "parser_expat.h"


namespace core {
    namespace service {
        namespace expat {

            node_expat::node_expat(parser_expat* parser, node_expat* parent, int depth, node::_t_on_parsed_node on_parsed, const char* tag, const char**atts):node(tag, parent, depth, on_parsed),_parser(parser) {
                /*
                Implementar lectura de atts
                this->set_attribute(id, value);
                */
                for (size_t i =0; atts[i]; i+=2) {
                    this->set_attribute(atts[i], atts[i+1]);
                    }

                __walker_depth = depth;
                _old_user_data = XML_GetUserData(_parser->get_parser());
                __container = new expat_handler_container(this);
                XML_SetUserData(_parser->get_parser(), __container);
                }

            node_expat::~node_expat() {
                delete __container;
                }

            void node_expat::on_start_tag(const char* pszName, const char** papszAttrs) {
                ++__walker_depth;
                node_expat* elem = _parser->create(this, pszName, papszAttrs, __walker_depth);
                if (elem) {
                    _children.push_back(elem);
                    }
                }

            void node_expat::on_end_tag(const char* pszName) {
                --__walker_depth;
                _data = __data.str();
                this->finished();
                XML_SetUserData(_parser->get_parser(), _old_user_data);
                }

            void node_expat::character_data(const char* pszName, int len) {
                __data << std::string(pszName).substr(0, len);
                }

            }
        }
    }