#! /bin/env bash

HEADER_PATH=/usr/local/include/vega
SDK_PATH=/opt/vega-sdk
RISCV_TOOLCHAIN_PATH=/opt/riscv-toolchain
MINIRC=/etc/minirc.aries

NORMAL=$(tput sgr0)
MAGENTA=$(tput setaf 5)

if [[ "$EUID" != 0 ]]
then 
    echo "${MAGENTA}Please run the script with root privileges!${NORMAL}"
    echo "Try sudo $0"
    exit
fi

if [ -d "$HEADER_PATH" ];then
    rm -rf $HEADER_PATH
fi

if [ -d "$SDK_PATH" ];then
    rm -rf $SDK_PATH
fi

if [ -d "$RISCV_TOOLCHAIN_PATH" ];then
    rm -rf $RISCV_TOOLCHAIN_PATH
fi

if [ -f "$MINIRC" ];then
    rm $MINIRC
fi

