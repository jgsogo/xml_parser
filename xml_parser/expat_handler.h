
#pragma once


namespace core {
    namespace service {
        namespace expat {

            struct expat_handler {
                virtual void on_start_tag(const char* pszName, const char** papszAttrs) = 0;
                virtual void on_end_tag(const char* pszName) = 0;
                virtual void character_data(const char* pszName, int len) = 0;
                };           

            struct expat_handler_container {
                expat_handler_container(expat_handler* item) : _item(item) {};
                expat_handler* _item;
                };

            }
        }
    }