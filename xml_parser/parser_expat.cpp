
#include "stdafx.h"
#include <cstring>
#include "parser_expat.h"

#include "node_expat_allocator.h"
#include "node_expat.h"

#ifdef _WIN32
    #define CALL_CONVENTION __cdecl
#else
    #define CALL_CONVENTION __attribute__((cdecl))
#endif // _WIN32

namespace core {
    namespace service {
        namespace expat {

            //callbacks
            void CALL_CONVENTION _start_element(void* userData, const XML_Char* name, const XML_Char** atts) {
                static_cast<expat_handler_container*>(userData)->_item->on_start_tag(name, atts);
                };
            void CALL_CONVENTION _end_element(void *userData, const XML_Char* name) {
                static_cast<expat_handler_container*>(userData)->_item->on_end_tag(name);
                };
            void CALL_CONVENTION _character_data_handler(void *userData, const XML_Char* txt, int len) {
                static_cast<expat_handler_container*>(userData)->_item->character_data(txt, len);
                };


            parser_expat::parser_expat() {
                depth = 0;
                }

            parser_expat::~parser_expat() {
                //XML_ParserFree(parser);
                }

            void parser_expat::reset() {
                __parser<node_expat_allocator>::reset();

                }

            int parser_expat::parse(FILE *buffer, const std::string &main_tag, _t_f_status f_status) {
                parser = XML_ParserCreate(NULL);
                XML_SetElementHandler(parser, _start_element, _end_element);
                XML_SetCharacterDataHandler(parser, _character_data_handler);

                char buf[1024], *aux;
                int done = 0;
                expat_handler_container* aux_container = new expat_handler_container(this);
                XML_SetUserData(parser, aux_container);
                aux = fgets(buf, 1024, buffer);
                while (aux) {
                    if (!XML_Parse(parser, buf, std::strlen(buf), done)) {
                        LOG_ERROR("Expat error on line '" << XML_GetErrorLineNumber(parser) << "', column '" << XML_GetErrorColumnNumber(parser) << "': " << XML_ErrorString(XML_GetErrorCode(parser)) << "");
                        return -1;
                        }
                    aux = fgets(buf, 1024, buffer);
                    }
                delete aux_container;

                XML_ParserFree(parser);
                return 0;
                }

            node_expat* parser_expat::create(node_expat* parent, const char* tag, const char**atts, int depth) {
                node_expat* elem = 0;
                _t_node_allocator_map::const_iterator it = _node_allocator_map.find(tag);
                if (it!=_node_allocator_map.end()) {
                    elem = it->second->allocate(this, parent, depth, tag, atts);
                    }
                else {
                    elem = new node_expat(this, parent, depth, nullptr, tag, atts);
                    }
                if (elem) {_nodes.push_back(elem);}
                return elem;
                }

            void parser_expat::on_start_tag(const char* pszName, const char** papszAttrs) {
                ++depth;
                this->create(0, pszName, papszAttrs, depth);
                }

            void parser_expat::on_end_tag(const char* pszName) {
                --depth;
                }

            void parser_expat::character_data(const char* pszName, int len) {
                }


            }
        }
    }
