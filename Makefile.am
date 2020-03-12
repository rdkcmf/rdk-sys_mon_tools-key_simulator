##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
SUBDIRS =
DIST_SUBDIRS =

# the list of header files that belong to the library (to be installed later)
AM_CFLAGS = -Wl,-rpath=/usr/lib/ \
	$(DBUS_CFLAGS) $(DIRECT_CFLAGS) $(FUSION_CFLAGS) $(GLIB_CFLAGS) \
	-I$(PKG_CONFIG_SYSROOT_DIR)${includedir}/rdk/iarmbus \
	-I$(PKG_CONFIG_SYSROOT_DIR)${includedir}/rdk/iarmmgrs/ir \
	-I$(PKG_CONFIG_SYSROOT_DIR)${includedir}/rdk/iarmmgrs-hal \
	-L$(PKG_CONFIG_SYSROOT_DIR)/usr/lib/


include_HEADERS = $(top_srcdir)/RDKIrKeyCodes.h

bin_PROGRAMS = keySimulator

keySimulator_SOURCES=IARM_BUS_UIEventSimulator.c
keySimulator_LDADD = $(DIRECT_LIBS) $(FUSION_LIBS) $(GLIB_LIBS) -lIARMBus $(DBUS_LIBS) -luinput
