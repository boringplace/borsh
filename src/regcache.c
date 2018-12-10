/**
 * \file regcache.c
 *
 * \brief Database interaction routines.
 *
 * \details This file encapsulates all the functionality needed to
 * interact with the user database.
 */

#include "config.h"
#include "system.h"
/* SQLite3 primitives are already included here. */
#include "regcache.h"

#if !defined(BORSH_SCHEMA)
/**
 * \brief SQLite3 command to create user data table.
 */
#define BORSH_SCHEMA "CREATE TABLE IF NOT EXISTS borsh_register" \
    "(" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "username TEXT UNIQUE," \
        "email TEXT UNIQUE," \
        "regcode TEXT UNIQUE" \
    ");"
#endif /* !defined(BORSH_SCHEMA) */

#if !defined(BORSH_IF_USER_EXISTS)
/**
 * \brief SQLite3 command to check if user is present in the table.
 */
#define BORSH_IF_USER_EXISTS(USERNAME) "SELECT EXISTS" \
    "(SELECT 1 FROM borsh_register WHERE username=\"USERNAME\" LIMIT 1);"
#endif /* !defined(BORSH_IF_USER_EXISTS) */

#if !defined(BORSH_ADD_USER)
/**
 * \brief Add new user for verification or throw exception.
 */
#define BORSH_ADD_USER(USERNAME, EMAIL, REGCODE) "INSERT INTO borsh_register" \
    "(username, email, regcode)" \
    "VALUES (USERNAME, EMAIL, REGCODE);"
#endif /* !defined(BORSH_ADD_USER) */

/**
 * \brief SQLite3 database instance we'ree working with.
 *
 * \details This instance visibility is limited to translation unit
 * because it's the only known way of data encapsulation for C99 AFAIK.
 */
static sqlite3 * db;

int
bsh_connect_database(char * _Nonnull dbpath) {
    int retcode = sqlite3_open(dbpath, &db);
    return retcode;
}

int
bsh_disconnect_database() {
    sqlite3_close(db);
    return 0;
}

int
bsh_deploy_schema() {
    char * schema = BORSH_SCHEMA;
    int retcode = sqlite3_exec(db, schema, NULL, NULL, NULL);
    return retcode;
}

int
bsh_user_exists(char const * _Nonnull username) {
    char * check_user_sql = BORSH_IF_USER_EXISTS(username);
    int retcode = sqlite3_exec(db, check_user_sql, NULL, NULL, NULL);
    return retcode;
}

int
bsh_user(char const * _Nonnull username) {
    return bsh_deploy_schema();
}

