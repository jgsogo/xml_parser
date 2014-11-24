
#include "stdafx.h"
#include "node.h"

namespace core {
    namespace service {

		const static std::string empty_string = "";

        node::node(const std::string &tag, node* parent, int depth, node::_t_on_parsed_node fn):_tag(tag),_parent(parent),_depth(depth), _on_finished(fn) {};
        node::~node() {};

        void node::finished() const {
            if (_on_finished) {
                _on_finished(*this);
                }
            }

        void node::set_attribute(const std::string &id, const std::string &value, const bool& override) {
            _t_attributes::const_iterator it = _attributes.find(id);
            if (it == _attributes.end()) {
                _attributes.insert(std::make_pair(id, value));
                }
            else {
                if (!override) {
                    LOG_ERROR("Attribute '" << id << "' already in node '" << this->get_tag() << "'");
                    }
                else {
                    _attributes[id] = value;
                    }
                }
            };


        bool node::has_attribute(const std::string &id) const {
			return (_attributes.find(id) != _attributes.end());
            }
        
		const node* node::get_child(const std::string& name) const {
                    _t_children::const_iterator it = _children.begin();
					while(it != _children.end()){
						if((*it)->get_tag().compare(name) == 0){
							break;
						}			
						it++;
					}
                    if (it!=_children.end()) {
                        return *it;
                        }
                    else {
                        return 0;
                        }
                    };

        const std::string& node::get_attribute(const std::string &id, bool &has_attribute) const {
            _t_attributes::const_iterator it = _attributes.find(id);
            if (it == _attributes.end()) {
                has_attribute = false;
                return empty_string;
                }
            else {
                has_attribute = true;
                return it->second;
                }
            }


        }
    }