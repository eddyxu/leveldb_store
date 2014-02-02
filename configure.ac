#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT([leveldb_store], [0.0.1], [eddyxu@gmail.com])
AM_INIT_AUTOMAKE([color-tests parallel-tests])
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([store/leveldb_store.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB
AC_LANG([C++])

# Checks for libraries.
# check is snappy-devel is installed, needed by leveldb
AC_CHECK_LIB([snappy], [snappy_compress], [], [AC_MSG_ERROR([libsnappy was not found.])])
# use system leveldb
AC_CHECK_LIB([leveldb], [leveldb_open], [], [AC_MSG_ERROR([libleveldb was not found.])], [-lsnappy -lpthread])
AC_CHECK_LIB([glog], [openlog], [], [AC_MSG_ERROR(google-glog was not found.)])
AX_BOOST_BASE([1.53])
AX_BOOST_FILESYSTEM([1.53])
AX_BOOST_SYSTEM([1.53])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AX_CXX_COMPILE_STDCXX_11(noext)
if test "$ac_cv_cxx_compile_cxx11" = no ; then
	AC_MSG_ERROR("It requires C++ 11 to build.!")
fi

# Checks for library functions.

CXXFLAGS="-Wall -Wextra -static -pedantic -Wunused-value $CXXFLAGS"
AM_CXXFLAGS="-isystem \$(top_srcdir)/lib/gmock-1.7.0/include"
AM_CXXFLAGS="$AM_CXXFLAGS -isystem \$(top_srcdir)/lib/gmock-1.7.0/gtest/include"
AM_LDFLAGS="-L\$(top_srcdir)/lib/gmock-1.7.0/lib"
AM_LDFLAGS="$AM_LDFLAGS -L\$(top_srcdir)/lib/gmock-1.7.0/gtest/lib"
AC_SUBST(CXXFLAGS)
AC_SUBST(AM_LDFLAGS)
AC_SUBST(AM_CXXFLAGS)

AC_CONFIG_FILES([Makefile
				 store/Makefile])
AC_OUTPUT
