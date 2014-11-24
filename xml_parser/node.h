
#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>

#include "xml_parser/xml_parser_export.h"

#if  _WIN32 && _MSC_VER <= 1500
	#include "boost/function.hpp"
	#include <boost/function/function1.hpp>
#elif __unix || __linux
	#include "boost/function.hpp"
	#include <boost/function/function1.hpp>
#endif

namespace core {
    namespace service {

        class XML_PARSER_EXPORT node {
            public:
#if _WIN32 && _MSC_VER <= 1500
				typedef boost::function1<void,const node&> _t_on_parsed_node;
#elif __linux || __unix
                typedef boost::function1<void, const node&> _t_on_parsed_node;
#else
				typedef std::function<void (const node&)> _t_on_parsed_node;
#endif
                typedef std::map<std::string, std::string> _t_attributes;
                typedef std::vector<node*> _t_children;
            public:
                node(const std::string &tag, node* parent, int depth, _t_on_parsed_node fn);
                virtual ~node();

                virtual void finished() const;

                void set_attribute(const std::string &id, const std::string &value, const bool& override=false);

                const int& get_depth() const { return _depth;};
                const std::string& get_tag() const { return _tag;};
                bool has_data() const { return !_data.empty();};
                const std::string& get_data() const { return _data;};

                bool has_attribute(const std::string &name) const;
                const std::string& get_attribute(const std::string &name, bool &has_attribute) const;
                const _t_attributes& get_attributes() const { return _attributes;};

                const _t_children& get_children() const { return _children;};
				const node* get_child(const std::string& name) const;
            protected:
                _t_on_parsed_node _on_finished;
                int _depth;
                node* _parent;
                std::string _tag;
                std::string _data;
                _t_attributes _attributes;
                _t_children _children;

            };

        inline std::ostream& operator<<(std::ostream& os, const node& nodo) {
            os << "<" << nodo.get_tag();
            const node::_t_attributes& attrs = nodo.get_attributes();
            node::_t_attributes::const_iterator it;
            for (it = attrs.begin(); it!=attrs.end(); ++it) {
                os << " " << it->first << "=\"" << it->second << "\"";
                }
            os << ">";
            os << nodo.get_data();
            os << "</" << nodo.get_tag() << ">";
            return os;
            };

        }
    }
