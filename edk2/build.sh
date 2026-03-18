#!/bin/sh

COMPILER_PATH=$1
EDK2_PATH=$2
export PATH="$COMPILER_PATH:$PATH"
export EDK_TOOLS_PATH="$EDK2_PATH/BaseTools"
export PACKAGES_PATH="$EDK2_PATH:$(dirname $(cd $(dirname $0);pwd))"
. "$EDK2_PATH/edksetup.sh" --reconfig
make -C "$EDK2_PATH/BaseTools"

build -y report.txt -Y COMPILE_INFO -a $3 -t $4 -b $5 -p $6
