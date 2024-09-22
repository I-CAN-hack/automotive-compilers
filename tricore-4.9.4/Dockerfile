FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
RUN apt-get update && apt-get install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo git

WORKDIR /src
RUN git clone --depth=1 https://github.com/volumit/package_494.git

ENV TARGET_ARCH="tricore-elf"
ENV TOOLCHAIN_NAME="gcc-${TARGET_ARCH}"
ENV TOOLCHAIN_PATH="/opt/${TOOLCHAIN_NAME}"
ENV PATH="${TOOLCHAIN_PATH}/bin:${PATH}"

# Build binutils
WORKDIR /build/binutils
RUN chmod +x /src/package_494/binutils/configure
RUN CFLAGS="-Wno-error -fcommon" /src/package_494/binutils/configure \
    --target=${TARGET_ARCH} \
    --prefix=${TOOLCHAIN_PATH} \
    --disable-nls
RUN  make -j$(nproc) all
RUN  make install


# Build gcc
WORKDIR /build/gcc
RUN chmod +x /src/package_494/gcc/configure
RUN chmod +x /src/package_494/gcc/move-if-change
RUN CFLAGS="-Wno-error -fcommon" /src/package_494/gcc/configure \
    --target=${TARGET_ARCH} \
    --prefix=${TOOLCHAIN_PATH} \
    --enable-languages=c \
    --without-headers \
    --with-gnu-as \
    --with-gnu-ld \
    --disable-shared \
    --disable-libssp \
    --disable-threads \
    --disable-nls \
    --with-newlib \
    --with-licenser=no

# Compile flags from volumit prebuilt toolchain
# Configured with: ../../../share/HOST/AURIX_MINGW/SRC/package_494/gcc/configure LDFLAGS=-static CXXFLAGS=-Wno-c++11-compat --target=tricore-elf --enable-lib32 --disable-lib64 --prefix=/home/dummy/tricore_494_linux --enable-languages=c,c++ --enable-c99 --enable-long-long --enable-checking --enable-nls --enable-static --disable-threads --disable-shared --with-headers=yes --with-newlib=yes --enable-mingw-wildcard --disable-libstdcxx-pch --enable-newlib-elix-level=3 --enable-newlib-io-long-long --disable-newlib-supplied-syscalls --disable-libssp --disable-test-suite --with-licenser=no --with-pkgversion=GPL_HIGHTEC_GCC494 --with-bugurl=https://community.infineon.com/t5/AURIX/bd-p/AURIX

RUN make -j$(nproc) all-gcc
RUN make install-gcc

WORKDIR /src
