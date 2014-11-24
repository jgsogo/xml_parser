
#pragma once 

#include <sstream>

namespace core {
    namespace service {
        
        class node;

        namespace expat {

            class parser_expat;
            struct expat_handler;
            struct expat_handler_container;

            class node_expat : public node, public expat_handler {
                public:
                    node_expat(parser_expat* parser, node_expat* parent, int depth, node::_t_on_parsed_node on_parsed, const char* tag, const char**atts);
                    virtual ~node_expat();

                    virtual void on_start_tag(const char* pszName, const char** papszAttrs);
                    virtual void on_end_tag(const char* pszName);
                    virtual void character_data(const char* pszName, int len);

                protected:
                    int __walker_depth;
                    parser_expat* _parser;
                    void* _old_user_data;
                    std::stringstream __data;
                    expat_handler_container* __container;
                };

            }
        }
    }