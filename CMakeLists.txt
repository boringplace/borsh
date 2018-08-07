cmake_minimum_required(VERSION 3.0)

project(boringshell
	VERSION 0.0.1
	LANGUAGES C)

include(CheckCCompilerFlag)

include_directories(
	/usr/include
	/usr/local/include)

# Block of variables for config.h
if (NOT BORSH_VERSION)
	set(BORSH_VERSION "0.0.1")
endif()
if (NOT BORSH_PACKAGE)
	set(BORSH_PACKAGE "borsh")
endif()
if (NOT BORSH_PACKAGE_NAME)
	set(BORSH_PACKAGE_NAME "Boring Shell")
endif()
if (NOT BORSH_PACKAGE_BUGREPORT)
	set(BORSH_PACKAGE_BUGREPORT "sin@altlinux.org")
endif()
if (NOT USER_PREFIX)
	set(USER_PREFIX "")
endif()
if (NOT REGISTER_USERNAME)
	set(REGISTER_USERNAME "register")
endif()
if (NOT PEOPLE_DIR)
	set(PEOPLE_DIR "/people")
endif()
if (NOT CMD_DIR)
	set(CMD_DIR "/var/lib/${REGISTER_USERNAME}/bin")
endif()

add_executable(borsh
	${boringshell_BINARY_DIR}/config.h
	src/borsh.c
	src/shell.c)

target_include_directories(borsh PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_BINARY_DIR})

set_property(TARGET borsh PROPERTY C_STANDARD 99)

function(check_compiler_flags flags)
	list(APPEND CFLAGS ${flags} ${ARGN})
	foreach (CFLAG IN LISTS CFLAGS)
		check_c_compiler_flag(${CFLAG} FLAG_SUPPORTED)
		if (FLAG_SUPPORTED)
			message(STATUS "Compiler flag supported: ${CFLAG}")
		else()
			message(FATAL_ERROR "Compiler flag not supported: ${CFLAG}")
		endif()
	endforeach()
endfunction()

set(CLANG_COMPILER_FLAGS -g)
set(GCC_COMPILER_FLAGS -gdwarf-4 -gsplit-dwarf)
set(PROJECT_COMPILER_FLAGS)
if (${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
	set(PROJECT_COMPILER_FLAGS ${CLANG_COMPILER_FLAGS})
elseif(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
	set(PROJECT_COMPILER_FLAGS ${GCC_COMPILER_FLAGS})
else()
	message(WARNING "Unsupported compiler detected, no specific compiler flags will be set.")
endif()
message(STATUS "The following compiler flags will be set: ${PROJECT_COMPILER_FLAGS}")
check_compiler_flags(${PROJECT_COMPILER_FLAGS})
target_compile_options(borsh PRIVATE ${PROJECT_COMPILER_FLAGS})

configure_file(config.h.in config.h)
configure_file(Doxyfile.in Doxyfile)

# Target to generate developers' documentation for borsh.
add_custom_target(borsh-dev-doc ALL
	COMMAND doxygen Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating developers' documentation for borsh")

add_dependencies(borsh-dev-doc
	borsh)

