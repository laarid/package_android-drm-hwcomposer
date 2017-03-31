# android-drm-hwcomposer versioning
# ---------------------------------
# To make new release:
#
#   laarid_micro_version += 1
#   laarid_interface_revision += 1
#
# if any functions have been added:
#
#   laarid_micro_version += 1
#   laarid_interface_revision = 0
#
#   or
#
#   laarid_minor_version += 1
#   laarid_micro_version = 0
#   laarid_interface_revision = 0
#
# if backwards compatibility has been broken:
#
#   laarid_major_version += 1
#   laarid_minor_version = 0
#   laarid_micro_version = 0
#   laarid_interface_revision = 0
m4_define([laarid_major_version], [0])
m4_define([laarid_minor_version], [0])
m4_define([laarid_micro_version], [1])
m4_define([laarid_interface_revision], [0])
m4_define([laarid_api_version], [laarid_major_version.0])
m4_define([laarid_release_number], [laarid_major_version])
m4_define([laarid_version],
  [laarid_major_version.laarid_minor_version.laarid_micro_version])

# Require autoconf 2.69 for aarch64
AC_PREREQ(2.69)

AC_INIT([android-drm-hwcomposer], [laarid_version],
  [https://github.com/laarid/package_android-drm-hwcomposer/issues], [],
  [https://github.com/laarid/package_android-drm-hwcomposer])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([drmhwcomposer.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects no-define tar-ustar])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

LAARID_MAJOR_VERSION=laarid_major_version
LAARID_MINOR_VERSION=laarid_minor_version
LAARID_MICRO_VERSION=laarid_micro_version
LAARID_API_VERSION=laarid_api_version
LAARID_RELEASE_NUMBER=laarid_release_number
AC_SUBST([LAARID_MAJOR_VERSION])
AC_SUBST([LAARID_MINOR_VERSION])
AC_SUBST([LAARID_MICRO_VERSION])
AC_SUBST([LAARID_API_VERSION])
AC_SUBST([LAARID_RELEASE_NUMBER])

# Define _GNU_SOURCE etc. where appropriate, e.g. for strptime() on glibc
AC_USE_SYSTEM_EXTENSIONS

# Large file support
# ------------------
AC_SYS_LARGEFILE

# Host environment
# ----------------
AC_CANONICAL_HOST

AM_PROG_AR
AM_PROG_AS
AC_PROG_CC
AC_PROG_CXX
PKG_PROG_PKG_CONFIG([0.24])

# libtool versioning
# ------------------
LT_INIT

# System dlloader
# ---------------
LT_LIB_DLLOAD

LT_OUTPUT

# Thread support
# --------------
AX_PTHREAD
dnl AX_PTHREADS leaves PTHREAD_LIBS empty for gcc and sets PTHREAD_CFLAGS
dnl to -pthread, which causes problems if we need -lpthread to appear in
dnl pkgconfig files.
test -z "$PTHREAD_LIBS" && PTHREAD_LIBS="-lpthread"

# Required libraries
# ------------------

LIBDRM_REQUIRED_VERSION=2.4.66
SYSTEMCORE_API_VERSION=0.0
SYSTEMCORE_REQUIRED_VERSION=0.0.18
HARDWARE_API_VERSION=0.0
HARDWARE_REQUIRED_VERSION=0.0.1
GRALLOC_DRM_API_VERSION=0.0
GRALLOC_DRM_REQUIRED_VERSION=0.0.3
FRAMEWORK_NATIVE_API_VERSION=0.0
FRAMEWORK_NATIVE_REQUIRED_VERSION=0.0.3
AC_SUBST([LIBDRM_REQUIRED_VERSION])
AC_SUBST([SYSTEMCORE_API_VERSION])
AC_SUBST([SYSTEMCORE_REQUIRED_VERSION])
AC_SUBST([HARDWARE_API_VERSION])
AC_SUBST([HARDWARE_REQUIRED_VERSION])
AC_SUBST([GRALLOC_DRM_API_VERSION])
AC_SUBST([GRALLOC_DRM_REQUIRED_VERSION])
AC_SUBST([FRAMEWORK_NATIVE_API_VERSION])
AC_SUBST([FRAMEWORK_NATIVE_REQUIRED_VERSION])

PKG_CHECK_MODULES([LIBDRM], [libdrm >= $LIBDRM_REQUIRED_VERSION])
PKG_CHECK_MODULES([SYSTEMCORE],
  [android-log-$SYSTEMCORE_API_VERSION >= $SYSTEMCORE_REQUIRED_VERSION
  android-cutils-$SYSTEMCORE_API_VERSION >= $SYSTEMCORE_REQUIRED_VERSION
  android-sync-$SYSTEMCORE_API_VERSION >= $SYSTEMCORE_REQUIRED_VERSION
  android-utils-$SYSTEMCORE_API_VERSION >= $SYSTEMCORE_REQUIRED_VERSION])
PKG_CHECK_MODULES([FRAMEWORK_NATIVE],
  [android-frameworks-native-$FRAMEWORK_NATIVE_API_VERSION >= $FRAMEWORK_NATIVE_REQUIRED_VERSION
  android-ui-$FRAMEWORK_NATIVE_API_VERSION >= $FRAMEWORK_NATIVE_REQUIRED_VERSION
  android-egl-$FRAMEWORK_NATIVE_API_VERSION >= $FRAMEWORK_NATIVE_REQUIRED_VERSION
  android-glesv2-$FRAMEWORK_NATIVE_API_VERSION >= $FRAMEWORK_NATIVE_REQUIRED_VERSION])
PKG_CHECK_MODULES([HARDWARE], [android-hardware-$HARDWARE_API_VERSION >= $HARDWARE_REQUIRED_VERSION])
PKG_CHECK_MODULES([GRALLOC_DRM], [android-gralloc-drm-$GRALLOC_DRM_API_VERSION >= $GRALLOC_DRM_REQUIRED_VERSION])

# Options
# -------
with_drm_buffer_importer=generic
AC_ARG_WITH([drm-buffer-importer],
  [AS_HELP_STRING([--with-drm-buffer-importer], [select DRM buffer importer])])
AM_CONDITIONAL([WITH_DRM_BUFFER_IMPORTER_GENERIC], [test x$with_drm_buffer_importer = xgeneric])
AM_CONDITIONAL([WITH_DRM_BUFFER_IMPORTER_NVIDIA], [test x$with_drm_buffer_importer = xnvidia])

AC_CONFIG_FILES([
  Makefile
])
AC_OUTPUT
