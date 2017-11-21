/* borsh.c -- initial boring shell.

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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#define _GNU_SOURCE

#include "system.h"

#include <errno.h>
#include <error.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <syslog.h>

static void __attribute__((noreturn)) exec_program (const char *program, const char *arg)
{
    execlp (program, program, arg, NULL);
    syslog(LOG_ERR, "fail to exec \"%s\": %s", program, strerror(errno));
    exit(EXIT_FAILURE);
}

static int run_program (const char *program, const char *arg)
{
    pid_t pid = fork();

    if (pid < 0) {
        syslog(LOG_ERR, "fail to fork: %s", strerror(errno));
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        exec_program (program, arg);

    } else {
        int status;
        int ret = waitpid (pid, &status, 0);
        if (ret < 0) {
            syslog(LOG_WARNING, "fail to wait: %s", strerror(errno));
            return EXIT_FAILURE;
        } else
            syslog(LOG_NOTICE, "done for wait: %s", strerror(errno));
    }
    return EXIT_SUCCESS;
}

int shell (void)
{
    return run_program ("dash", NULL);
}

int register_shell (const char* email)
{
    return run_program ("boring-register", email);
}

int main_shell (int argc, char *argv[])
{
    uid_t uid = getuid();

    if (!uid)
        error(EXIT_FAILURE, 0, _("must be non-root"));

    struct passwd *pw = getpwuid(uid);

    if (!pw)
        error(EXIT_FAILURE, errno, "getpwuid");

    const char *pwname = pw->pw_name;
    const char *register_email = NULL;

    if (strncmp(pwname, REGISTER_USERNAME, sizeof(REGISTER_USERNAME) - 1) == 0 &&
        pwname[sizeof(REGISTER_USERNAME)] != '\0')
        goto enter_register_shell;

    const char *boring_user = pwname + sizeof(USER_PREFIX) - 1;

    if (strncmp(pwname, USER_PREFIX, sizeof(USER_PREFIX) - 1) ||
        boring_user[0] == '\0')
        error(EXIT_FAILURE, 0, "invalid account name");

    char *home;

    if (asprintf(&home, "%s/%s", PEOPLE_DIR, boring_user) < 0)
        error(EXIT_FAILURE, errno, "asprintf");

    if (chdir(home) < 0)
        error(EXIT_FAILURE, errno, "chdir");

    const char *tmpdir = getenv("TMPDIR");

    if (tmpdir)
        tmpdir = strdup(tmpdir);

    if (clearenv() < 0)
        error(EXIT_FAILURE, errno, "clearenv");

    if ((setenv("USER", pw->pw_name, 1) < 0) ||
        (setenv("LOGNAME", pw->pw_name, 1) < 0) ||
        (setenv("HOME", home, 1) < 0) ||
        (setenv("PATH", CMD_DIR ":/bin:/usr/bin", 1) < 0) ||
        (setenv("BORING_USER", boring_user, 1) < 0) ||
        (setenv("BORING_USER_PREFIX", USER_PREFIX, 1) < 0) ||
        (tmpdir && *tmpdir && setenv("TMPDIR", tmpdir, 1) < 0))
        error(EXIT_FAILURE, errno, "setenv");

    if (argc == 1)
    {
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

    if (argc == 2)
        register_email = argv[1];

    if (argc == 2 || argc == 3)
    {
        openlog("boring-register", LOG_PID, LOG_USER);
        syslog(LOG_INFO, "register: %s email", register_email ? register_email : "(unknown)");
        int ret = register_shell(register_email);
        syslog(LOG_INFO, "register: exit");
        closelog();
        exit(ret);
    }

    error(0, 0, "%d arguments is wrong for register.\r", argc);
    return EXIT_FAILURE;
}
