/**
 * \file shell.h
 *
 * \brief Boring Shell command invocation functions.
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

#if !defined(_SHELL_H)
#define _SHELL_H (1)

static void __attribute__((noreturn))
exec_program (const char *program, const char *arg);

#if defined(__FreeBSD__)
/**
 * \brief Workaround function for error.h
 *
 * \details The initial code used \c error(3) from \c error.h which
 * exists only for Linux. This function is a little workaround to avoid
 * conditional compilation and/or rewrite of the source file.
 */
void
error(int exit_code,
		int error_num,
		const char * str,
		...);
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
run_program(const char *program, const char *arg);

/**
 * \brief Run Bourne Shell.
 */
int
shell(void);

/**
 * \brief Run interactive external program to register user via e-mail.
 *
 * \param [in] email String containing e-mail to send verification to.
 *
 * \return Application exit code.
 */
int
register_shell(const char* email);

/**
 * \brief Main loop.
 *
 * \param [in] argc \c argc as it is passed to \c main() function.
 *
 * \param [in] argv \c argv as it is passed to \c main() function.
 *
 * \return Exit code.
 */
int
main_shell(int argc, char *argv[]);

#endif /* SHELL_H */

