
project(xml_parser CXX)

set(XML_PARSER_MAJOR_VERSION 1)
set(XML_PARSER_MINOR_VERSION 0)
set(XML_PARSER_PATCH_VERSION 0)
set(XML_PARSER_VERSION ${XML_PARSER_MAJOR_VERSION}.${XML_PARSER_MINOR_VERSION}.${XML_PARSER_PATCH_VERSION})

if(BIICODE)
    include (GenerateExportHeader)
    INIT_BIICODE_BLOCK()

    #SET(BUILD_SHARED_LIBS 1) # Let the end user decide
    add_subdirectory(xml_parser)
    add_subdirectory(examples)

    SET(BII_LIB_SRC ${XML_PARSER_SRC_FILES})
    SET(BII_examples_xml_parser_basic_main_SRC ${EXAMPLES_XML_PARSER_BASIC_SRC_FILES})
       
    ADD_BIICODE_TARGETS()              

    generate_export_header(${BII_LIB_TARGET} BASE_NAME xml_parser) # Necesito ponerlo después de "ADD_BIICODE_TARGETS"
    target_include_directories( ${BII_LIB_TARGET} PUBLIC "${PROJECT_BINARY_DIR}/../") # Necesito ponerlo después de "ADD_BIICODE_TARGETS"

else()
    cmake_minimum_required(VERSION 2.8)

    # Set default for CMAKE_INSTALL_PREFIX
    SET(CORE_INSTALL_PREFIX "C:/libraries/core/service" CACHE PATH "Prefix prepended to
    install directories")
    SET(CMAKE_INSTALL_PREFIX "${CORE_INSTALL_PREFIX}" CACHE INTERNAL "Prefix
    prepended to install directories" FORCE)

    # Offer the user the choice of overriding the installation directories
    set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
    set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
    set(INSTALL_INCLUDE_DIR include CACHE PATH
    "Installation directory for header files")
    if(WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKE_DIR CMake)
    else()
    set(DEF_INSTALL_CMAKE_DIR lib/CMake/xml_parser)
    endif()
    set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
    "Installation directory for CMake files")

    # Make relative paths absolute (needed later on)
    foreach(p LIB BIN INCLUDE CMAKE)
    set(var INSTALL_${p}_DIR)
    if(NOT IS_ABSOLUTE "${${var}}")
      set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif()
    endforeach()

    # set up include-directories
    include_directories(
    "${PROJECT_SOURCE_DIR}"   # to find xml_parser/txttable_parser.h
    "${PROJECT_BINARY_DIR}")  # to find xml_parser/config.h

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Add sub-directories    
    add_subdirectory(xml_parser)
    OPTION(BUILD_EXAMPLES "Build xml_parser examples" OFF)
    if(${BUILD_EXAMPLES})
                add_subdirectory(examples) 
    endif()

    # The interesting stuff goes here
    # ===============================

    # Add all targets to the build-tree export set
    export(TARGETS xml_parser
    FILE "${PROJECT_BINARY_DIR}/xml_parser-targets.cmake")


    # Export the package for use from the build-tree
    # (this registers the build-tree with a global CMake-registry)
    export(PACKAGE xml_parser)

    # Create the xml_parser-config.cmake and xml_parser-config-version files
    file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
     "${INSTALL_INCLUDE_DIR}")
    # ... for the build tree
    set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
    configure_file(xml_parser-config.cmake.in
    "${PROJECT_BINARY_DIR}/xml_parser-config.cmake" @ONLY)
    # ... for the install tree
    set(CONF_INCLUDE_DIRS "\${XML_PARSER_CMAKE_DIR}/${REL_INCLUDE_DIR}")
    configure_file(xml_parser-config.cmake.in
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/xml_parser-config.cmake" @ONLY)
    # ... for both
    configure_file(xml_parser-config-version.cmake.in
    "${PROJECT_BINARY_DIR}/xml_parser-config-version.cmake" @ONLY)

    # Install the xml_parser-config.cmake and xml_parser-config-version.cmake
    install(FILES
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/xml_parser-config.cmake"
    "${PROJECT_BINARY_DIR}/xml_parser-config-version.cmake"
    DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

    # Install the export set for use with the install-tree
    install(EXPORT xml_parser-targets DESTINATION
    "${INSTALL_CMAKE_DIR}" COMPONENT dev)
endif()

message(STATUS "Files will be installed at ${CMAKE_INSTALL_PREFIX}")