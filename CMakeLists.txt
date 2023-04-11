cmake_minimum_required(VERSION 3.0)

project(MiniDbg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )

###################
# git submodule
###################
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/ext/libelfin/Makefile")
    message(FATAL_ERROR "The submodule libelfin were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/ext/linenoise/Makefile")
    message(FATAL_ERROR "The submodule linenoise were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#################
# dependencies
#################
add_custom_target(
   libelfin
   COMMAND make
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/ext/libelfin
)


###################
# set includes
###################
include_directories(ext/libelfin ext/linenoise include)

##################
# minidbg
##################
set (MINIDBG_SRCS 
        minidbg.cc 
        src/debugger.cc 
        src/utils.cc
        src/breakpoint.cc
    )
add_executable(minidbg ${MINIDBG_SRCS} ext/linenoise/linenoise.c)
target_link_libraries(minidbg
                      ${PROJECT_SOURCE_DIR}/ext/libelfin/dwarf/libdwarf++.so
                      ${PROJECT_SOURCE_DIR}/ext/libelfin/elf/libelf++.so)
add_dependencies(minidbg libelfin)

#################
# subdirectories
#################

add_subdirectory(test)