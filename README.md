# Lyra

Lyra is an alternative SDK for CDAC's VEGA series of micro-controllers, encompassing its development, documentation, and resources for a seamless experience. The name is inspired by the constellation hosting one of the brightest night stars - Vega.

### **DISCLAIMER** 
The project is NOT affiliated to or endorsed by CDAC (Centre for Developemnet of Advanced Computing). This is an independent project with original works.

It comes with no warranty, programming done with a mix of documentation, reverse-enginerring and experimentation.

## Getting Started

#### Supported Platforms
- Linux
- Windows 10, 11 (through [WSL2](https://learn.microsoft.com/en-us/windows/wsl/install))
- MacOS (Coming Soon)

_REMARK_ : The SPI flasher tool is only supported on `x86_64` host machines for now.

### Set-up
Just run the setup shell script 
```sh
sudo ./setup.sh
```

### Environment Setup

The setup script alreads sets up the `VEGA_SDK_PATH` variable in your default shell profile. So any editor works. See [Template Project](examples/template-project/)

My personal recommendation is Microsoft's [Visual Studio Code](https://code.visualstudio.com).

Install LLVM's clangd extension (Idendtifier: `llvm-vs-code-extensions.vscode-clangd`) for code completion and static code analysis.

Windows users utilizing WSL, read [Connect USB Devices](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) to connect the board to the WSL virtual machine.

---

## LICENSE

Licensed under the [MIT License](LICENSE)

All product names, trademarks, and registered trademarks such as VEGA, THEJAS32 and ARIES are the property of Centre for Development of Advanced Computing (CDAC)

**LEGAL NOTICE**: This repository, including any and all of its forks and derivatives, may NOT be used in the development or training of any machine learning model of any kind, without the explicit permission of the owner of the original repository.


