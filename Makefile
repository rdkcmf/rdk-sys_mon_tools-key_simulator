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
EXECUTABLE = keySimulator 

ifeq ($(USE_IARM),y)
	IARM        = $(COMBINED_ROOT)/iarm
	IARM_CFLAGS = -I$(IARM)/  -I$(DFB_ROOT)/usr/local/include/directfb 
	IARM_LDFLAGS=-L$(IARM)/install/lib -L$(DFB_LIB)
ifeq ($(USE_DBUS),y)
       IARM_LIBS = -ldirect -ldbus-1 -lstdc++ -lfusion -lnexus -lUIIARM -lpthread
else
        IARM_LIBS = -ldirect -lfusiondale -lfusion -lnexus -lUIIARM -lpthread
endif
	OBJS=IARM_UIEventSimulator
endif

ifeq ($(USE_IARM_BUS),y)
	IARM        = $(COMBINED_ROOT)/iarmbus
	IARM_MGR    = $(COMBINED_ROOT)/iarmmgrs
	IARM_CFLAGS = -I$(IARM)/core/include -I$(DFB_ROOT)/usr/local/include/directfb 
	IARM_CFLAGS += -I$(IARM_MGR)/generic/ir/include -I$(IARM_MGR)/generic/hal/include -I$(IARM)/core/ 
	IARM_LDFLAGS=-L$(IARM)/install/ -L$(DFB_LIB) -L$(OPENSOURCE_BASE)/lib  -L$(GLIB_LIBRARY_PATH)/
ifeq ($(USE_DBUS),y)
       IARM_LIBS = -ldirect -ldbus-1 -lstdc++ -lfusion -lIARMBus -lpthread
else
        IARM_LIBS = -ldirect -lfusiondale -lfusion -lIARMBus -lpthread 
endif
	OBJS=IARM_BUS_UIEventSimulator
endif

all: clean install
	@echo "Finished Building $(EXECUTABLE) tool....."
	
exe:  
	@echo "Building $(EXECUTABLE) tool....."
	$(CC) $(IARM_CFLAGS) -c $(OBJS).c
	$(CXX) $(IARM_CFLAGS) $(IARM_LIBS) $(IARM_LDFLAGS) $(GLIBS) $(OBJS).o -o $(EXECUTABLE)

clean:
	@rm -rf *.o
	@rm -rf $(EXECUTABLE) 

install: exe
	@cp $(EXECUTABLE) $(FSROOT)/usr/local/bin 
uninstall:
	@rm $(EXECUTABLE) $(FSROOT)/usr/local/bin 
