/**
 * \file regcache.h
 *
 * \brief Encapsulation of database interaction functionality
 *
 * \details This file encapsulates all the functions related to
 * working with SQLite3 regarding to storing information about users
 * who try to register.
 */

#pragma once

#include <sqlite3.h>

#if !defined(_BORSH_REGCACHE_H)
#define _BORSH_REGCACHE_H (1)

/**
 * \brief Connect to SQLite3 instance.
 */
int
bsh_connect_database(char * dbpath);

/**
 * \brief Disconnect from SQLite3 instance.
 */
int
bsh_disconnect_database();

/**
 * \brief create all tables on first connection.
 */
int
bsh_deploy_schema();

/**
 * \brief Check if the specified user exists in the table.
 */
int
bsh_user_exists(char const * username);

/**
 * \brief Create new username entry if missing.
 */
int
bsh_user(char const * username);

#endif /* !defined(_BORSH_REGCACHE_H) */

