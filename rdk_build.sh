#!/bin/bash
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

#######################################
#
# Build Framework standard script for
#
# Key simulator component

# use -e to fail on any shell issue
# -e is the requirement from Build Framework
set -ex

# default PATHs - use `man readlink` for more info
# the path to combined build
export RDK_PROJECT_ROOT_PATH=${RDK_PROJECT_ROOT_PATH-`readlink -m ..`}
export COMBINED_ROOT=$RDK_PROJECT_ROOT_PATH



# fsroot and toolchain (valid for all devices)
export RDK_FSROOT_PATH=${RDK_FSROOT_PATH-`readlink -m $RDK_PROJECT_ROOT_PATH/sdk/fsroot/ramdisk`}
export RDK_TOOLCHAIN_PATH=${RDK_TOOLCHAIN_PATH-`readlink -m $RDK_PROJECT_ROOT_PATH/sdk/toolchain/staging_dir`}




# parse arguments
INITIAL_ARGS=$@

function usage()
{
    set +x
    echo "Usage: `basename $0` [-h|--help] [-v|--verbose] [action]"
    echo "    -h    --help                  : this help"
    echo "    -v    --verbose               : verbose output"
    echo "    -p    --platform  =PLATFORM   : specify platform for IARMBus"
    echo
    echo "Supported actions:"
    echo "      configure, clean, build (DEFAULT), rebuild, install"
}

eval set -- "$GETOPT"

while true; do
  case "$1" in
    -h | --help ) usage; exit 0 ;;
    -v | --verbose ) set -x ;;
    -p | --platform ) CC_PLATFORM="$2" ; shift ;;
    -- ) shift; break;;
    * ) break;;
  esac
  shift
done

ARGS=$@


# component-specific vars
export RDK_PLATFORM_SOC=${RDK_PLATFORM_SOC-broadcom}
export PLATFORM_SOC=$RDK_PLATFORM_SOC
export CC_PLATFORM=${CC_PLATFORM-$RDK_PLATFORM_SOC}
CC_PATH=$COMBINED_ROOT/sys_mon_tools/key_simulator
export FSROOT=${RDK_FSROOT_PATH}
export TOOLCHAIN_DIR=${RDK_TOOLCHAIN_PATH}
export BUILDS_DIR=$RDK_PROJECT_ROOT_PATH


# functional modules

function configure()
{
    echo "here"
    true #use this function to perform any pre-build configuration
}

function clean()
{
    true #use this function to provide instructions to clean workspace
}

function build()
{
    CURR_DIR=`pwd`
    cd ${CC_PATH}
    if [ $RDK_PLATFORM_SOC = "intel" ]; then
	export TOOLCHAIN_DIR=$COMBINED_ROOT/sdk/toolchain/staging_dir
	export CROSS_TOOLCHAIN=$TOOLCHAIN_DIR
	export CROSS_COMPILE=$CROSS_TOOLCHAIN/bin/i686-cm-linux
	export CC=$CROSS_COMPILE-gcc
	export CXX=$CROSS_COMPILE-g++
	export OPENSOURCE_BASE=$COMBINED_ROOT/opensource
	export DFB_ROOT=$TOOLCHAIN_DIR
	export DFB_LIB=$TOOLCHAIN_DIR/lib
	export IARM_PATH=$BUILDS_DIR/iarmbus
	export FUSION_PATH=$OPENSOURCE_BASE/src/FusionDale
	export SDK_FSROOT=$COMBINED_ROOT/sdk/fsroot/ramdisk
	export FSROOT=$COMBINED_ROOT/sdk/fsroot/ramdisk
        export GLIB_INCLUDE_PATH=$CROSS_TOOLCHAIN/include/glib-2.0/
        export GLIB_LIBRARY_PATH=$CROSS_TOOLCHAIN/lib/
        export GLIB_CONFIG_INCLUDE_PATH=$GLIB_LIBRARY_PATH/glib-2.0/
	export GLIBS='-lglib-2.0 -lz'
    elif [ $RDK_PLATFORM_SOC = "broadcom" ]; then
        echo "building for ${RDK_PLATFORM_DEVICE}..."
        export WORK_DIR=$BUILDS_DIR/work${RDK_PLATFORM_DEVICE^^}
		
		if [ ${RDK_PLATFORM_DEVICE} = "rng150" ];then
			if [ -f $BUILDS_DIR/sdk/scripts/setBcmEnv.sh ]; then
				. $BUILDS_DIR/sdk/scripts/setBcmEnv.sh		
			fi
			if [ -f $BUILDS_DIR/sdk/scripts/setBCMenv.sh ]; then
				. $BUILDS_DIR/sdk/scripts/setBCMenv.sh		
			fi
		else
		        . $BUILDS_DIR/build_scripts/setBCMenv.sh
		fi

        export MFR_PATH=$WORK_DIR/svn/sdk/mfrlib
    	export OPENSOURCE_BASE=$BUILDS_DIR/opensource
        export IARM_PATH=$BUILDS_DIR/iarmbus
    	export FUSION_PATH=$OPENSOURCE_BASE/FusionDale
        export FSROOT=$COMBINED_ROOT/sdk/fsroot/ramdisk
    	CROSS_COMPILE=mipsel-linux
        export CC=$CROSS_COMPILE-gcc
    	export CXX=$CROSS_COMPILE-g++
        export GLIB_INCLUDE_PATH=$FSROOT/usr/local/include/glib-2.0/
        export GLIB_LIBRARY_PATH=$FSROOT/usr/local/lib/
        export GLIBS='-lglib-2.0 -lintl -lz'
    elif [ $RDK_PLATFORM_SOC = "entropic" ]; then
      export SDK_CONFIG=stb597_V3_xi3
      export BUILD_DIR=$BUILDS_DIR
      source ${BUILD_DIR}/build_scripts/setupSDK.sh

      export FSROOT="${BUILD_DIR}/fsroot"

      export LDFLAGS="-L${GCC_BASE}/lib \
         -L${_TMTGTBUILDROOT}/comps/generated/lib/armgnu_linux_el_cortex-a9 \
         -L${_TMTGTBUILDROOT}/comps/generic_apps/usr/lib \
         -L${FSROOT}/usr/lib -L${FSROOT}/usr/local/lib"


      export OPENSOURCE_BASE="${BUILD_DIR}/opensource"
      export IARM_PATH="${BUILD_DIR}/iarmbus"
      export DFB_LIB="${_TMTGTBUILDROOT}/comps/generic_apps/usr/lib"
      export DFB_ROOT="${_TMTGTBUILDROOT}/comps/generic_apps/usr/include/directfb"
      export FUSION_PATH="${_TMTGTBUILDROOT}/comps/generic_apps/usr/include/fusiondale"
      export GLIB_INCLUDE_PATH="${_TMTGTBUILDROOT}/comps/generic_apps/usr/include/glib-2.0"
      export GLIB_CONFIG_INCLUDE_PATH="${_TMTGTBUILDROOT}/comps/generic_apps/usr/lib/glib-2.0"
      export GLIB_LIBRARY_PATH="${FSROOT}/appfs/lib"
      export GLIBS="-lglib-2.0 -lz"
      export DS_PATH="${BUILD_DIR}/devicesettings"

      export CFLAGS="-O2 -Wall -fPIC \
         -I${_TMTGTBUILDROOT}/comps/generic_apps/usr/include \
         -I${NXP_BASE_ROOT}/open_source_archive/linux/tools_glibc_${GCC_VERSION}/usr/include \
         -I${_TMTGTBUILDROOT}/comps/generic_apps/usr/include/glib-2.0 \
         -I${_TMTGTBUILDROOT}/comps/generic_apps/usr/lib/glib-2.0/include \
         -I${FSROOT}/usr/local/include/libxml2 \
         -I${FSROOT}/usr/local/include/libsoup-2.4 \
         -I ${DFB_ROOT} -I$FUSION_PATH \
         -I${FSROOT}/usr/local/include/gssdp-1.0"

      export CC="${GCC_PREFIX}-gcc --sysroot ${_TMSYSROOT} $CFLAGS" 
      export CXX="${GCC_PREFIX}-g++ --sysroot ${_TMSYSROOT} $CFLAGS" 
      export LD="${GCC_PREFIX}-ld --sysroot ${_TMSYSROOT}"
   elif [ $RDK_PLATFORM_SOC = "mstar" ]; then
	  CROSS_COMPILE=arm-none-linux-gnueabi
	  export GLIBS='-lglib-2.0 -lz'	  
	  FSROOT=$COMBINED_ROOT/sdk/fsroot
	  export IARM_PATH=$BUILDS_DIR/iarmbus
	  export DFB_ROOT=${FSROOT}
	  export GLIB_INCLUDE_PATH="${FSROOT}/usr/include/glib-2.0"
	  export GLIB_CONFIG_INCLUDE_PATH="${FSROOT}/usr/lib/glib-2.0/include"
	  export FUSION_PATH="${FSROOT}/usr/include/fusiondale"
	  export CFLAGS+="-O2 -Wall -fPIC -I./include -I${GLIB_INCLUDE_PATH} -I${GLIB_CONFIG_INCLUDE_PATH} -I${FUSION_PATH} \
         -I${FSROOT}/usr/include \
         -I${FSROOT}/usr/include/directfb \
         -I${FSROOT}/usr/include/libsoup-2.4\
         -I${FSROOT}/usr/include/gssdp-1.0"
	  export LDFLAGS+="-Wl,-rpath,${FSROOT}/vendor/lib/utopia -L${FSROOT}/usr/lib"		
	  export DFB_LIB=${FSROOT}/vendor/lib
	  export OPENSOURCE_BASE=${FSROOT}/usr
	  export CC="$CROSS_COMPILE-gcc $CFLAGS"
	  export CXX="$CROSS_COMPILE-g++ $CFLAGS $LDFLAGS"     
    fi
    if [ -d $IARM_PATH ]; then
	  export USE_IARM_BUS="y"
    else
          export IARM_PATH=$COMBINED_ROOT/iarm
	  export USE_IARM="y"
    fi	
          
    make

    cd $CURR_DIR

}

function rebuild()
{
    clean
    build
}

function install()
{
    true
}


# run the logic

#these args are what left untouched after parse_args
HIT=false

for i in "$ARGS"; do
    case $i in
        configure)  HIT=true; configure ;;
        clean)      HIT=true; clean ;;
        build)      HIT=true; build ;;
        rebuild)    HIT=true; rebuild ;;
        install)    HIT=true; install ;;
        *)
            #skip unknown
        ;;
    esac
done

# if not HIT do build by default
if ! $HIT; then
  build
fi
