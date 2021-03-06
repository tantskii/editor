cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    message(STATUS "TRAVIS_BUILD_NUMBER environment variable is not defined. Run 'export TRAVIS_BUILD_NUMBER=1'.")
endif()

project(editor VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories(src)
add_subdirectory(src)

set_target_properties(editor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

FIND_PACKAGE(Doxygen REQUIRED dot)
if (DOXYGEN_FOUND)
    message(STATUS "Doxygen is found:)")
    
    set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/src)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/doc)
    set(DOXYGEN_RECURSIVE NO)
    set(DOXYGEN_PROJECT_NAME ${CMAKE_PROJECT_NAME})
    set(DOXYGEN_PROJECT_NUMBER 0.0.$ENV{TRAVIS_BUILD_NUMBER})
    
    configure_file(doxygen.conf.in doxygen.conf)
    add_custom_target(editor_doc COMMAND ${DOXYGEN_EXECUTABLE} doxygen.conf)
else ()
    message(STATUS "WARNING: Doxygen is not found:(")
endif()


if (MSVC)
    target_compile_options(editor PRIVATE
        /W4
    )
else ()
    target_compile_options(editor PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT tihon1997@gmail.com)
include(CPack)

# enable_testing()
# add_test(matrix_test matrix_test)
