/**
 * \file system.h
 *
 * \brief system-dependent declarations; include this first.
 *
 * \license
   Copyright 1996, 2005, 2006, 2007, 2008 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef _BORSH_SYSTEM_H
#define _BORSH_SYSTEM_H (1)

#if defined(__linux__)
#   if !defined(_GNU_SOURCE)
#      define _GNU_SOURCE (1)
#   endif /* !defined(_GNU_SOURCE) */
#endif /* __linux__ */

/* Assume ANSI C89 headers are available.  */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Use POSIX headers.  If they are not available, we use the substitute
   provided by gnulib.  */
#include <getopt.h>
#include <unistd.h>

/* Avoid gettext this time.  */
#define _(str) (str)

/* Portable way to work with environment variables */
extern char** environ;

#endif /* !defined(_BORSH_SYSTEM_H) */

