#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.50)
AC_INIT([libhookwrite], [0.0.1], [masato@bz2.jp])
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE([libhookwrite], [0.0.1])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([dl], [dlsym], ,AC_MSG_ERROR([dl is needed to compile $PACKAGE_NAME]))

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_UTIME_NULL
AC_CHECK_FUNCS([utime])

AC_CONFIG_FILES([Makefile
                 libhookwrite.spec
                 src/Makefile])
AC_OUTPUT
