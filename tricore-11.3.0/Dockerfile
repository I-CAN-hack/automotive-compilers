FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
RUN apt-get update && apt-get install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo git

WORKDIR /src
RUN git clone --depth=1 https://github.com/EEESlab/tricore-binutils-gdb.git
RUN git clone --depth=1 https://github.com/EEESlab/tricore-gcc.git

ENV TARGET_ARCH="tricore-elf"
ENV TOOLCHAIN_NAME="gcc-${TARGET_ARCH}"
ENV TOOLCHAIN_PATH="/opt/${TOOLCHAIN_NAME}"
ENV PATH="${TOOLCHAIN_PATH}/bin:${PATH}"

# Build binutils
WORKDIR /build/binutils
RUN /src/tricore-binutils-gdb/configure \
    --target=${TARGET_ARCH} \
    --prefix=${TOOLCHAIN_PATH} \
    --disable-nls \
    --disable-werror
RUN  make -j$(nproc) all
RUN  make install

# Build gcc
WORKDIR /build/gcc
RUN /src/tricore-gcc/configure \
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
    --with-newlib

RUN make -j$(nproc) all-gcc
RUN make install-gcc

WORKDIR /src
