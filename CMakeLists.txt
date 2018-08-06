cmake_minimum_required(VERSION 3.0)

project(boringshell C)

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

configure_file(config.h.in config.h)

