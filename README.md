# XML Parser

[![Build status](https://ci.appveyor.com/api/projects/status/0msq8um4jtkrjc68?svg=true)](https://ci.appveyor.com/project/jgsogo/xml-parser)


## Description

Tiny library to parse XML files using callbacks

Github repo (@jgsogo): https://github.com/jgsogo/xml_parser


## Usage


### Compile and install dependencies

At this moment only the EXPAT parser is implemented, so you will need to:

 1. install [expat library](https://github.com/jgsogo/expat) first.
 1. compile and install this library, you can use CMake or Biicode (recommended, see below).

### Create a parser

In order to work with the library the first thing you need is to create an instance of a parser. There are two possibilities to get an instance:

 1. Creating an object of the parser:
 
    <pre><code>#include "xml_parser/parser_expat.h"
    
    int main() {
        core::service::expat::parser_expat parser;
        // Play with the parser
    }
    </code></pre>

 1. Creating through the library interface
    
    <pre><code>#include "xml_parser/api.h"
     
    int main() {
        core::service::parser* parser;
        build_xml_parser(parser, "expat");        
        // Play with the parser        
        delete_xml_parser(parser);
    }
    </code></pre>

    
### Parse a file

Create as many callback functions as needed and associate them with the xml nodes to parse:

<pre><code>
// An example function that prints information about a node
auto log_node = [](const core::service::node& node) {
    std::cout << node.get_tag() << std::endl;
    auto attribs = node.get_attributes();
    for (auto it = attribs.begin(); it != attribs.end(); ++it) {
        std::cout << "\t" << it->first << ": " << it->second << std::endl;
    }
    if (node.has_data()) {
        std::cout << "\tDATA: " << node.get_data() << std::endl;
    }
    // Access childrent using node.get_childrent()
}

// Assign it to a given tag
parser.register_tag("xml_tag", log_node);
</code></pre>


And let the parser run

<pre><code>
parser.parse_file("filename.xml", "<root-tag>")
</code></pre>


## Usage with Biicode

To use it with [Biicode](https://www.biicode.com/) just include the block

<pre><code>
#include "jgsogo/xml_parser/xml_parser/parser_expat.h"
</code></pre>

and let Biicode resolve the dependencies

<pre><code>
bii find
bii cpp:build
</code></pre>


## Work ahead

This a concept library in development, there are several challenges ahead:

 * detach callback execution from file parsing
