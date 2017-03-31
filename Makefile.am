# Copyright (C) 2015 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# Distribution
# ------------
EXTRA_DIST =
BUILT_SOURCES =
CLEANFILES =
DISTCLEANFILES =
MAINTAINERCLEANFILES = \
    $(GITIGNORE_MAINTAINERCLEANFILES_TOPLEVEL) \
    $(GITIGNORE_MAINTAINERCLEANFILES_M4_LIBTOOL) \
    $(GITIGNORE_MAINTAINERCLEANFILES_MAKEFILE_IN) \
    $(srcdir)/ChangeLog \
    $(srcdir)/INSTALL

# We're running CI in docker, which reports host architecture as host,
# not the docker image architecture as we expected, so specifying the
# host/build information is necessary here.
DISTCHECK_CONFIGURE_FLAGS = \
    --host=$(host_alias) \
    --build=$(build_alias) \
    --disable-dependency-tracking \
    --disable-maintainer-mode

GITIGNOREFILES = \
    build \
    debian \
    $(DIST_ARCHIVES)

# Common/global flags
# -------------------
AM_CPPFLAGS = \
    -include config.h \
    -DNDEBUG

AM_CFLAGS = \
    -Wall -Werror \
    -Wa,--noexecstack \
    -std=gnu11

AM_CXXFLAGS = \
    -Wall -Werror \
    -Wa,--noexecstack \
    -std=gnu++11

AM_LDFLAGS = \
    -Wl,-z,noexecstack \
    -Wl,--as-needed \
    -Wl,--no-undefined \
    -no-undefined

hwlibdir = $(libdir)/hw
hwlib_LTLIBRARIES = hwcomposer.drm.la

hwcomposer_drm_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(LIBDRM_CFLAGS) \
    $(SYSTEMCORE_CFLAGS) \
    $(FRAMEWORK_NATIVE_CFLAGS) \
    $(HARDWARE_CFLAGS) \
    $(GRALLOC_DRM_CFLAGS) \
    -DANDROID_EGL_PLATFORM
if WITH_DRM_BUFFER_IMPORTER_GENERIC
hwcomposer_drm_la_CPPFLAGS += \
    -DUSE_DRM_GENERIC_IMPORTER
else
if WITH_DRM_BUFFER_IMPORTER_NVIDIA
hwcomposer_drm_la_CPPFLAGS += \
    -DUSE_NVIDIA_IMPORTER
endif
endif

hwcomposer_drm_la_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    $(PTHREAD_CFLAGS) \
    -Wno-unused-variable \
    -Wno-unused-function \
    -Wno-unused-label

hwcomposer_drm_la_SOURCES = \
    %reldir%/autofd.h \
    %reldir%/autogl.h \
    %reldir%/autolock.cpp \
    %reldir%/autolock.h \
    %reldir%/drmresources.cpp \
    %reldir%/drmcomposition.cpp \
    %reldir%/drmcompositor.cpp \
    %reldir%/drmcompositor.h \
    %reldir%/drmcompositorworker.cpp \
    %reldir%/drmcompositorworker.h \
    %reldir%/drmconnector.cpp \
    %reldir%/drmconnector.h \
    %reldir%/drmcrtc.cpp \
    %reldir%/drmcrtc.h \
    %reldir%/drmdisplaycomposition.cpp \
    %reldir%/drmdisplaycomposition.h \
    %reldir%/drmdisplaycompositor.cpp \
    %reldir%/drmdisplaycompositor.h \
    %reldir%/drmencoder.cpp \
    %reldir%/drmencoder.h \
    %reldir%/drmeventlistener.cpp \
    %reldir%/drmeventlistener.h \
    %reldir%/drmframebuffer.h \
    %reldir%/drmhwcgralloc.h \
    %reldir%/drmhwcomposer.h \
    %reldir%/drmmode.cpp \
    %reldir%/drmmode.h \
    %reldir%/drmplane.cpp \
    %reldir%/drmplane.h \
    %reldir%/drmproperty.cpp \
    %reldir%/drmproperty.h \
    %reldir%/drmresources.h \
    %reldir%/glworker.cpp \
    %reldir%/glworker.h \
    %reldir%/hwcomposer.cpp \
    %reldir%/platform.cpp \
    %reldir%/platform.h \
    %reldir%/platformdrmgeneric.cpp \
    %reldir%/platformdrmgeneric.h \
    %reldir%/platformnv.cpp \
    %reldir%/platformnv.h \
    %reldir%/separate_rects.cpp \
    %reldir%/separate_rects.h \
    %reldir%/virtualcompositorworker.cpp \
    %reldir%/virtualcompositorworker.h \
    %reldir%/vsyncworker.cpp \
    %reldir%/vsyncworker.h \
    %reldir%/worker.cpp \
    %reldir%/worker.h

hwcomposer_drm_la_LDFLAGS = \
    $(AM_LDFLAGS) \
    -shared \
    -module \
    -avoid-version

hwcomposer_drm_la_LIBADD = \
    $(PTHREAD_LIBS) \
    $(LIBDRM_LIBS) \
    $(SYSTEMCORE_LIBS) \
    $(HARDWARE_LIBS) \
    $(FRAMEWORK_NATIVE_LIBS)

CLEANFILES += $(BUILT_SOURCES)
GITIGNOREFILES += $(BUILT_SOURCES)

-include $(top_srcdir)/git.mk
