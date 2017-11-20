dnl Process this file with autoconf to produce a configure script.
dnl
dnl This file is free software; as a special exception the author gives
dnl unlimited permission to copy and/or distribute it, with or without
dnl modifications, as long as this notice is preserved.
dnl
dnl This program is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
dnl implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([SarFSC Borsh], [0.0.1], [bug-borsh@boringplace.org])

dnl Must come before AM_INIT_AUTOMAKE.
AM_INIT_AUTOMAKE([foreign])

# Minimum Autoconf version required.
AC_PREREQ(2.60)

# Where to generate output; srcdir location.
AC_CONFIG_HEADERS(config.h)
AC_CONFIG_SRCDIR([src/borsh.c])

dnl Checks for programs.
# We need a C compiler.
AC_PROG_CC
AC_GNU_SOURCE

AC_CONFIG_FILES([Makefile
           man/Makefile
           src/Makefile])
AC_OUTPUT
