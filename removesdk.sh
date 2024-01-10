#! /bin/env bash

HEADER_PATH=/usr/local/include/vega
SDK_PATH=/opt/vega-sdk
RISCV_TOOLCHAIN_PATH=/opt/riscv-toolchain
MINIRC=/etc/minirc.aries
DEFAULT_SHELL=$(grep "$SUDO_USER" /etc/passwd | awk -F: '{print $7}' | awk -F/ '{print $NF}')
RC_FILE=/dev/zero

NORMAL=$(tput sgr0)
MAGENTA=$(tput setaf 5)

if [[ "$EUID" != 0 ]]
then 
    echo "${MAGENTA}Please run the script with administrator privileges!${NORMAL}"
    echo "Try sudo $0"
    exit
fi

if [ -d "$HEADER_PATH" ];then
    rm -rf $HEADER_PATH
fi

if [ -d "$SDK_PATH" ];then
    rm -rf $SDK_PATH
fi

printf "Remove the RISC-V toolchain (Y/n):"
read -r input 

if [ -z "$input" ] || [ "${input^^}" = "Y" ]; then

    if [ -d "$RISCV_TOOLCHAIN_PATH" ];then
        rm -rf $RISCV_TOOLCHAIN_PATH
    fi
fi

if [ -f "$MINIRC" ];then
    rm $MINIRC
fi

case "$DEFAULT_SHELL" in
  "bash")
    RC_FILE=/home/$SUDO_USER/.bashrc
    ;;
  "zsh")
    RC_FILE=/home/$SUDO_USER/.zshrc
    ;;
  *)
    printf "Unsupported shell: %s
    Manually delete the environment variable VEGA_SDK_PATH in your shell rc file",$DEFAULT_SHELL
    ;;
esac

# Remove the environment variable from rc file
sed -i '/VEGA_SDK_PATH/d' "$RC_FILE"

#EOF
