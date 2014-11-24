
#pragma once

#include "parser.h"
#include "expat_handler.h"

struct XML_ParserStruct;

namespace core {
    namespace service {
        namespace expat {

            class node_expat_allocator;
            class node_expat;

            class XML_PARSER_EXPORT parser_expat : public __parser<node_expat_allocator>, public expat_handler {
                public:
                    parser_expat();
                    virtual ~parser_expat();

                    XML_ParserStruct*& get_parser() { return parser;};

                    virtual int parse(FILE *buffer, const std::string &main_tag, _t_f_status f_status =0);
                    virtual void reset();

                    virtual void on_start_tag(const char* pszName, const char** papszAttrs);
                    virtual void on_end_tag(const char* pszName);
                    virtual void character_data(const char* pszName, int len);

                    node_expat* create(node_expat* parent, const char* tag, const char**atts, int depth);

                protected:

                private:
                    int depth;
                    XML_ParserStruct* parser;
                };

            }
        }
    }
