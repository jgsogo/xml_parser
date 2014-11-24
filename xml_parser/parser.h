
#pragma once

#include <map>
#include <vector>
#include "xml_parser/xml_parser_export.h"
#include "node.h"

namespace core {
    namespace service {

#if _WIN32 && _MSC_VER <= 1500
        typedef void (*_t_f_status)(const std::string&);
#elif __unix || __linux
        typedef void (*_t_f_status)(const std::string&);
#else
        typedef std::function<void (const std::string&)> _t_f_status;
#endif

        struct parser {
            public:
                //parser() {};
                //virtual ~parser() {};
                virtual int register_tag(const std::string &tag, node::_t_on_parsed_node fn= 0) = 0;
				virtual int parse_file(const std::string &file, const std::string &main_tag, _t_f_status f_status =0) = 0;
                virtual int parse(FILE *buffer, const std::string &main_tag, _t_f_status f_status =0) = 0;
                virtual void reset() = 0;
            };

        template <class Allocator>
        class XML_PARSER_EXPORT __parser : public parser {
            public:
                __parser();
                virtual ~__parser();

                virtual int register_tag(const std::string &tag, node::_t_on_parsed_node fn= 0);
                virtual int parse_file(const std::string &file, const std::string &main_tag, _t_f_status f_status =0);

                virtual int parse(FILE *buffer, const std::string &main_tag, _t_f_status f =0);
                virtual void reset();

            protected:
                node* root;

                typedef std::vector<node*> _t_node_vector;
                _t_node_vector _nodes;

                typedef std::map<std::string, Allocator*> _t_node_allocator_map;
				_t_node_allocator_map _node_allocator_map;
            };

        }
    }
