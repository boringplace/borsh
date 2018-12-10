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

#pragma once

#if !defined(_BORSH_SHELL_H)
#define _BORSH_SHELL_H (1)

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
register_shell();

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

#endif /* !defined(_BORSH_SHELL_H) */

