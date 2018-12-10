/**
 * \file borsh.c -- initial boring shell.
 *
 * \license
   Copyright 2017 Saratov Free Software Center, Org.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"
#include "system.h"
#include "shell.h"
/* SQLite3 interaction procedures. */
#include "regcache.h"

#if defined(__linux__)
#    include <errno.h>
#    include <error.h>
#    include <ctype.h>
#    include <sys/types.h>
#    include <sys/wait.h>
#    include <pwd.h>
#    include <syslog.h>
#elif defined(__FreeBSD__)
#    include <sys/errno.h>
#    include <sys/ctype.h>
#    include <sys/types.h>
#    include <sys/wait.h>
#    include <pwd.h>
#    include <sys/syslog.h>
#endif /* __linux__ */

static void __attribute__((noreturn))
exec_program (const char *program, const char *arg) {
    execlp (program, program, arg, NULL);
    syslog(LOG_ERR, "fail to exec \"%s\": %s", program, strerror(errno));
    exit(EXIT_FAILURE);
}

#if defined(__FreeBSD__)
/**
 * \brief Workaround function for error.h
 *
 * \details The initial code used \c error(3) from \c error.h which
 * exists only for Linux. This function is a little workaround to avoid
 * conditional compilation and/or rewrite of the source file.
 */
static void
error(int exit_code,
        int error_num,
        const char * str,
        ...) {
    perror(str);
    exit(exit_code);
}
#endif /* __FreeBSD__ */

/**
 * \brief Run program from $PATH
 *
 * \param [in] program Program name
 *
 * \param [in] arg Arguments.
 *
 * \return Program exit code.
 */
static int
run_program (const char *program, const char *arg) {
    pid_t pid = fork();

    if (0 > pid) {
        syslog(LOG_ERR, "Failed to fork: %s", strerror(errno));
        return EXIT_FAILURE;
    }

    if (0 == pid) {
        exec_program (program, arg);

    } else {
        int status;
        int ret = waitpid (pid, &status, 0);
        if (0 > ret) {
            syslog(LOG_WARNING, "Failed to wait: %s", strerror(errno));
            return EXIT_FAILURE;
        } else {
            syslog(LOG_NOTICE, "Finished waiting: %s", strerror(errno));
        }
    }
    return EXIT_SUCCESS;
}

int
shell(void) {
    return run_program("/bin/sh", NULL);
}

int
register_shell() {
    int rc = bsh_connect_database("/var/db/borsh/borsh.sqlite3");
    if (!rc) {
        syslog(LOG_INFO, "Created database.");
        int retcode = bsh_user("nir");
        if (SQLITE_OK != retcode) {
            syslog(LOG_INFO, "Failed to create table.");
        }
        bsh_disconnect_database();
    } else {
        syslog(LOG_INFO, "Failed to create database.");
    }
    return 0;
}

int
main_shell(int const argc, char const * const * argv) {
/*    uid_t uid = getuid();
    if (!uid) error(EXIT_FAILURE, 0, _("must be non-root"));

    struct passwd *pw = getpwuid(uid);
    if (!pw) error(EXIT_FAILURE, errno, "getpwuid");

    const char *pwname = pw->pw_name;
    const char *register_email = NULL;

    if (0 == strncmp(pwname, REGISTER_USERNAME, sizeof(REGISTER_USERNAME) - 1) &&
        pwname[sizeof(REGISTER_USERNAME)] != '\0')
        goto enter_register_shell;

    const char *boring_user = pwname + sizeof(USER_PREFIX) - 1;

    if (strncmp(pwname, USER_PREFIX, sizeof(USER_PREFIX) - 1) ||
        '\0' == boring_user[0])
        error(EXIT_FAILURE, 0, "invalid account name");

    char *home;

    if (0 > asprintf(&home, "%s/%s", PEOPLE_DIR, boring_user))
        error(EXIT_FAILURE, errno, "asprintf");

    if (0 > chdir(home)) error(EXIT_FAILURE, errno, "chdir");

    const char *tmpdir = getenv("TMPDIR");
    if (tmpdir) tmpdir = strdup(tmpdir);

    environ[0] = NULL;

    if ((setenv("USER", pw->pw_name, 1) < 0) ||
        (setenv("LOGNAME", pw->pw_name, 1) < 0) ||
        (setenv("HOME", home, 1) < 0) ||
        (setenv("PATH", CMD_DIR ":/bin:/usr/bin", 1) < 0) ||
        (setenv("BORING_USER", boring_user, 1) < 0) ||
        (setenv("BORING_USER_PREFIX", USER_PREFIX, 1) < 0) ||
        (tmpdir && *tmpdir && setenv("TMPDIR", tmpdir, 1) < 0))
        error(EXIT_FAILURE, errno, "setenv");

    if (argc == 1) {
        openlog("boring-shell", LOG_PID, LOG_USER);
        syslog(LOG_INFO, "enter user %s", boring_user);
        int ret = shell();
        syslog(LOG_INFO, "exit user %s", boring_user);
        closelog();
        exit(ret);
    }

    error(0, 0, "%d arguments is wrong for shell.\r", argc);
    return EXIT_FAILURE;

enter_register_shell:

    if (2 == argc) register_email = argv[1];

    if (2 == argc || 3 == argc) {
        openlog("boring-register", LOG_PID, LOG_USER);
        syslog(LOG_INFO, "register: %s email", register_email ? register_email : "(unknown)");
        int ret = register_shell(register_email);
        syslog(LOG_INFO, "register: exit");
        closelog();
        exit(ret);
    }

    error(0, 0, "%d arguments is wrong for register.\r", argc);
    return EXIT_FAILURE;*/
    return register_shell();
}

