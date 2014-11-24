
#include "stdafx.h"
#include "node_allocator.h"

namespace core {
    namespace service {

        node_allocator::node_allocator(node::_t_on_parsed_node f) : _on_parsed_node(f) {
            }
        
        node_allocator::~node_allocator() {
            }

        }
    }