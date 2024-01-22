#! /bin/env bash

# THEJAS32 SDK setup script
# Author - Arif B <arif.dev@pm.me>

# Colors require ncurses to be installed
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
MAGENTA=$(tput setaf 5)
CYAN=$(tput setaf 6)
NORMAL=$(tput sgr0)

set -e

HOST_ARCH=$(uname -m)
SETUP_PATH=$(realpath $PWD)
HEADER_PATH=/usr/local/include/vega
SDK_PATH=/opt/vega-sdk
RISCV_TOOLCHAIN_PATH=/opt/riscv-toolchain
DEFAULT_SHELL=$(grep "$SUDO_USER" /etc/passwd | awk -F: '{print $7}' | awk -F/ '{print $NF}')
RC_FILE=/dev/zero
MINICOM_CONFIG=/etc/minirc.aries

# Check if running as root
if [[ "$EUID" != 0 ]]
then 
    echo "${MAGENTA}Please run the script with administrator privileges!${NORMAL}"
    echo "Try sudo $0"
    exit
fi

# Install dependencies
if command -v apt &> /dev/null; then
    apt-get -y install make tar git minicom
elif command -v rpm &> /dev/null; then
    yum install -y make tar git minicom
elif command -v pacman &> /dev/null; then
    pacman -Sy make tar git minicom
else
    printf "${RED}Unsupported Distro! Please make sure the following packages are installed:${NORMAL}"
    printf "make\ntar\ngit\nminicom\n"
    printf "${YELLOW}Continue? (Y/n) :${NORMAL}"
    read input
    if [ ${input^^} = "N" ]; then
       exit
    fi
fi



# Copy header files
mkdir -p "$HEADER_PATH"
cp "$SETUP_PATH"/include/* "$HEADER_PATH"


# Create directory for SDK
mkdir -p "$SDK_PATH"

cp common/* "$SDK_PATH"
cp -r "$SETUP_PATH"/drivers "$SDK_PATH"
cp  "$SETUP_PATH"/tools/aries-flasher "$SDK_PATH"
cp  "$SETUP_PATH"/tools/xmodem-transfer "$SDK_PATH"


case "$DEFAULT_SHELL" in
  "bash")
    RC_FILE=/home/$SUDO_USER/.bashrc
    ;;
  "zsh")
    RC_FILE=/home/$SUDO_USER/.zshrc
    ;;
  *)
    printf "Unsupported shell: %s
    Manually export the environment variable VEGA_SDK_PATH in your shell rc file
    export VEGA_SDK_PATH=%s",$DEFAULT_SHELL,$VEGA_SDK_PATH
    ;;
esac

echo "export VEGA_SDK_PATH=$SDK_PATH" >> $RC_FILE


# Download RISC-V toolchain 
# WIP, Downloading a fixed release for Linux currently
printf "\n${YELLOW}Download RISC-V Toolchain? (Y/n) :${NORMAL}"
read -r input

if [ -z "$input" ] || [ "${input^^}" = "Y" ]; then

    if [ "$HOST_ARCH" = "x86_64" ];then
        TOOLCHAIN_URL=https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v13.2.0-2/xpack-riscv-none-elf-gcc-13.2.0-2-linux-x64.tar.gz
        flag=1
    elif [ "$HOST_ARCH" = "aarch64" ];then
        TOOLCHAIN_URL=https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v13.2.0-2/xpack-riscv-none-elf-gcc-13.2.0-2-linux-arm64.tar.gz
        flag=1
    else
        printf "${MAGENTA}Unsupported host architecture! Please create a pull request${NORMAL}"
        flag=0
    fi

    if [ "$flag" = 1 ];then
        mkdir -p $RISCV_TOOLCHAIN_PATH
        pushd $RISCV_TOOLCHAIN_PATH
        curl -OL "$TOOLCHAIN_URL"
        tar xzf *.tar.gz
        rm *.tar.gz
        extracted_dir=$(find . -maxdepth 1 -type d -name "xpack-*" -print -quit)

        if [ -n "$extracted_dir" ]; then
            bin_path="$(realpath "$extracted_dir")/bin"
        
            echo "export PATH=\$PATH:$bin_path" >> $RC_FILE
            popd
        fi
    fi
fi


#  Create minicom config

printf "
# THEJAS32 Minicom Configuration
pu port             /dev/ttyUSB0
pu baudrate         115200
pu bits             8
pu parity           N
pu stopbits         1
pu rtscts           No
" > $MINICOM_CONFIG


usermod -aG dialout $SUDO_USER

echo "${GREEN}Successfully Installed the SDK${NORMAL}"