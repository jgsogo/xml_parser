

#------------------------------------------
#   List source files
file(GLOB _headers "${PROJECT_SOURCE_DIR}/xml_parser/*.h")
file(GLOB _src "${PROJECT_SOURCE_DIR}/xml_parser/*.cpp")
set(XML_PARSER_SRC_FILES
              ${_headers}
              ${_src}
              ${PROJECT_SOURCE_DIR}/xml_parser/config.h.in
              ${PROJECT_SOURCE_DIR}/xml_parser/CMakeLists.txt              
              )
set(XML_PARSER_SRC_FILES ${XML_PARSER_SRC_FILES} PARENT_SCOPE)
configure_file(${PROJECT_SOURCE_DIR}/xml_parser/config.h.in "${PROJECT_BINARY_DIR}/config.h" @ONLY)


#------------------------------------------
#   Add export macro and
#       remove useless warnings
if(WIN32)
    # remove warning C4275: se ha utilizado una interfaz no de DLL class
    # remove warning C4996: 'standard function': This function or variable may be unsafe...
    # remove warning C4251: 'atribute' : class 'name' necesita tener una interfaz DLL...
    add_definitions(-D_CRT_SECURE_NO_WARNINGS /wd4275 /wd4251)
else()
    list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
endif(WIN32)
    
    
if(NOT BIICODE) 
    include (GenerateExportHeader)    
    include(../depends/cmake/use_precompiled_header2.cmake)
           
    # Look for expat
    include(../depends/cmake/expat_install.txt)
    EXPATInstall()
    include_directories( ${EXPAT_INCLUDE_DIR} )

    #------------------------------------------
    #        Build a library
    add_definitions(-D_UNICODE -DUNICODE)
    add_compiler_export_flags()
    add_library(xml_parser SHARED ${XML_PARSER_SRC_FILES})
    target_link_libraries(xml_parser ${EXPAT_LIBRARIES} )
    generate_export_header(xml_parser)

    use_precompiled_header2(
        xml_parser
        "stdafx.h"
        "stdafx.cpp"
        ${_src}
        )

    set_target_properties(xml_parser PROPERTIES
      PUBLIC_HEADER "api.h;parser_expat.h;parser.h;expat_handler.h;node.h;${CMAKE_CURRENT_BINARY_DIR}/config.h;${CMAKE_CURRENT_BINARY_DIR}/xml_parser_export.h;"
      LINKER_LANGUAGE CXX
      FOLDER "core/service"
      )

    install(TARGETS xml_parser
      # IMPORTANT: Add the xml_parser library to the "export-set"
      EXPORT xml_parser-targets
      RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
      LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
      ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
      PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/xml_parser"
        COMPONENT dev)
endif()
