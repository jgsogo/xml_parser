
#pragma once

#include "node.h"

namespace core {
    namespace service {

        class node_allocator {
            public:
                node_allocator(node::_t_on_parsed_node f);
                virtual ~node_allocator();
                //virtual node* allocate(parser* parser, node *parent, const char* tag, const char**atts) const;
            protected:
                node::_t_on_parsed_node _on_parsed_node;
            };

        }
    }