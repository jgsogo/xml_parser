
#pragma once

#include "node_allocator.h"
#include "node.h"
#include "expat_handler.h"
#include "node_expat.h"

namespace core {
    namespace service {
        namespace expat {

            class node_expat_allocator : node_allocator {
                public:
                    node_expat_allocator(node::_t_on_parsed_node f) : node_allocator(f) {};
                    virtual ~node_expat_allocator() {};
                    virtual node_expat* allocate(parser_expat* parser, node_expat *parent, int depth, const char* tag, const char**atts) const {
                        return new node_expat(parser, parent, depth, _on_parsed_node, tag, atts);
                        };
                protected:
                };

            }
        }
    }