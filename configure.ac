dnl Process this file with autoconf to produce a configure script.
dnl
dnl This file is free software; as a special exception the author gives
dnl unlimited permission to copy and/or distribute it, with or without
dnl modifications, as long as this notice is preserved.
dnl
dnl This program is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
dnl implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([Borsh], [0.0.1], [bug-borsh@boringplace.org])

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

# GNU help2man creates man pages from --help output; in many cases, this
# is sufficient, and obviates the need to maintain man pages separately.
# However, this means invoking executables, which we generally cannot do
# when cross-compiling, so we test to avoid that (the variable
# "cross_compiling" is set by AC_PROG_CC).
if test $cross_compiling = no; then
  AM_MISSING_PROG(HELP2MAN, help2man)
else
  HELP2MAN=:
fi

AC_SUBST(USER_PREFIX)
USER_PREFIX=
AC_ARG_WITH(userprefix, [  --with-userprefix=STRING      Prefix of boring username], [
if test "$withval" != yes
then USER_PREFIX=$withval
else AC_MSG_ERROR([proper usage is --with-userprefix=STRING])
fi])

AC_SUBST(PEOPLE_DIR)
PEOPLE_DIR=/people
AC_ARG_WITH(peopledir, [  --with-peopledir=STRING      Boring people home directory], [
if test "$withval" != yes
then PEOPLE_DIR=$withval
else AC_MSG_ERROR([proper usage is --with-peopledir=STRING])
fi])

AC_SUBST(REGISTER_USERNAME)
REGISTER_USERNAME=register
AC_ARG_WITH(userprefix, [  --with-registerusername=STRING      System register username], [
if test "$withval" != yes
then REGISTER_USERNAME=$withval
else AC_MSG_ERROR([proper usage is --with-registerusername=STRING])
fi])

AC_SUBST(CMD_DIR)
CMD_DIR=/var/lib/$REGISTER_USERNAME/bin
AC_ARG_WITH(cmddir, [  --with-cmddir=STRING      Register commands directory], [
if test "$withval" != yes
then CMD_DIR=$withval
else AC_MSG_ERROR([proper usage is --with-cmddir=STRING])
fi])

AC_CONFIG_FILES([Makefile
           man/Makefile
           src/borsh.sudoers
           src/Makefile])
AC_OUTPUT
