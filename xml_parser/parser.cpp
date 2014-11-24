
#include "stdafx.h"
#include "parser.h"

namespace core {
    namespace service {

        template <class T>
        __parser<T>::__parser() {
            root=0;
            }

        template <class T>
        __parser<T>::~__parser() {
            this->reset();
            }

        template <class T>
        int __parser<T>::register_tag(const std::string &tag, node::_t_on_parsed_node fn) {
            typename _t_node_allocator_map::const_iterator it = _node_allocator_map.find(tag);
            if (it==_node_allocator_map.end()) {
                _node_allocator_map.insert(std::make_pair(tag, new T(fn)));
                return 0;
                }
            LOG_WARN("There is already a function defined for tag '" << tag << "'");
            return -1;
            }

        template <class T>
        int __parser<T>::parse_file(const std::string &file, const std::string &main_tag, _t_f_status f_status) {
            int hRet = -1;
            FILE* f; f = fopen(file.c_str(), "r");
            if (f!=0) {
                LOG_DEBUG("Parsing file '" << file << "'");
                hRet = this->parse(f, main_tag, f_status);
                fclose(f);
                }
            LOG_PARAMS(else {)
                LOG_ERROR("File '" << file << "' does not exists");
            LOG_PARAMS(})
            return hRet;
            }

        template <class T>
        int __parser<T>::parse(FILE *buffer, const std::string &main_tag, _t_f_status f) {
            LOG_ERROR("Derived classes should implement this function");
            return -1;
            }

        template <class T>
        void __parser<T>::reset() {
            typename _t_node_allocator_map::iterator it;
            for (it = _node_allocator_map.begin(); it!=_node_allocator_map.end(); it++) {
                delete it->second;
                }
            _node_allocator_map.clear();

            _t_node_vector::iterator it_v;
            for (it_v = _nodes.begin(); it_v!=_nodes.end(); it_v++) {
                delete (*it_v);
                }
            _nodes.clear();
            }

        }
    }


#include "node_expat_allocator.h"
namespace core {
    namespace service {
        namespace expat {

            // No need to call, just to create function code.
            void temp_function() {
                __parser<node_expat_allocator> parser;
                }

            }
        }
    }
