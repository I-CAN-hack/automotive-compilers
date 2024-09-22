## Automotive Compilers
This repository contains Dockerfiles for building the GCC toolchain for the most common architectures used in automotive. I use these to quickly compile some shellcode, so only the minimal set of packages are compiled to build standalone executables. No standard libraries (e.g. newlib) are built.

## Supported Architectures:
- PowerPC VLE: GCC 4.9.4 from original sources, with patches from [NXP](https://github.com/nxp-auto-tools/s32ds_patches). Based on S32 Design Studio.
- TriCore:
  - GCC 4.9.4 with patches already applied from [volumit](https://github.com/volumit/package_494). Based on HighTec C.
  - GCC 11.3.0 with patches already applied from [EEESlab](https://github.com/EEESlab/tricore-gcc-toolchain-11.3.0/). Based on Aurix Design Studio (ADS).
- V850/RH850: GCC 13.2.0 from original sources.

## How to build
Each architecture contains a Dockerfile. There is also an example script in each architecture folder that builds the docker container, and compiles a bit of shellcode using the container.
