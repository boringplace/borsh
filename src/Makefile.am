# Makefile.am for borsh/src.
#
# Copyright 2017 Saratov Free Software Center, Org.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS = borsh
borsh_SOURCES = borsh.c shell.c system.h
borsh_CFLAGS = -DUSER_PREFIX=\"@USER_PREFIX@\" -DREGISTER_USERNAME=\"@REGISTER_USERNAME@\" -DPEOPLE_DIR=\"@PEOPLE_DIR@\" -DCMD_DIR=\"@CMD_DIR@\"
