C_PREREQ(2.59)
AC_INIT(AAC_RESAMPLER, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_FILES([Makefile src/Makefile]) 

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([faad.h])
AC_CHECK_HEADERS([samplerate.h])
AC_CHECK_HEADERS([sndfile.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_LIB([faad], [NeAACDecOpen])
AC_CHECK_LIB([samplerate], [src_new])
#AC_CHECK_LIB([sndfile], [sf_open_virtual])

AC_OUTPUT
