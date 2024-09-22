FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
RUN apt-get update && apt-get install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo git wget dos2unix

ENV BINUTILS_VERSION=2.28
ENV GCC_VERSION=4.9.4
ENV TARGET_ARCH="powerpc-eabivle"
ENV TOOLCHAIN_NAME="gcc-${TARGET_ARCH}"
ENV TOOLCHAIN_PATH="/opt/${TOOLCHAIN_NAME}"
ENV PATH="${TOOLCHAIN_PATH}/bin:${PATH}"

WORKDIR /src
RUN wget https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.bz2
RUN tar -xvf gcc-${GCC_VERSION}.tar.bz2

RUN wget https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.bz2
RUN tar -xvf binutils-${BINUTILS_VERSION}.tar.bz2

RUN git clone https://github.com/nxp-auto-tools/s32ds_patches.git

# Patch order from https://github.com/fpoussin/gcc-powerpc-eabivle
ENV BINUTILS_PATCHES="bin.2-28-aeabi-common \
    bin.2-28-vle-common \
    bin.2-28-spe2-common \
    bin.2-28-aeabi-binutils \
    bin.2-28-vle-binutils \
    bin.2-28-spe2-binutils \
    bin.2-28-plt \
    bin.2-28-booke2vle-binutils \
    bin.2-28-vleHyp \
    bin.2-28-efs2"

ENV GCC_PATCHES="gcc.aeabi-49x gcc.fix_regalloc_for_482 \
    gcc.rm_slow_tests-47 gcc.fix_mingw32 \
    gcc.rm_slow_tests-494 \
    gcc.e6500-FSF-49x gcc.no_power_builtins-48 \
    gcc.ld_unaligned-460 gcc.local_unaligned_altivec gcc.soft_float-470 \
    gcc.case_values-48 gcc.fix_pr63854_pass_manager \
    gcc.builtin_isel-49x gcc.builtin_isel_doc \
    gcc.experimental_move \
    gcc.widen_types-49x \
    gcc.extelim-v4-49x \
    gcc.extelim_vrp_kugan-v1-49x \
    gcc.e5500_mfocr \
    gcc.opt-array-offset-49x \
    gcc.load_on_store_bypass-48x \
    gcc.fix_constvector \
    gcc.fix_pr63908_unwind_info \
    gcc.have-pre-modify-disp-support-49x \
    gcc.fix_ENGR00298583_dwarf-vector-reg_49x \
    gcc.fix_MTWX51605-memset-array-init_48 \
    gcc.fix_altivec_constant_alignment-v2 \
    gcc.fix_altivec_reload_gs8 \
    gcc.fix_postfix_gimplifier \
    gcc.fix_adjust_address_cost \
    gcc.fix_adjust_sched_loopinv_cost \
    gcc.fix_e5500_mulli_pipeline \
    gcc.fix_e500mc_addi_pipeline \
    gcc.fix_ENGR00292364_debug_frame \
    gcc.fix_ENGR00215936_49x \
    gcc.enable_soft_multilib-49x gcc.fix_49x-doc \
    gcc.fix_emulation_spec_48 gcc.create_maeabi \
    gcc.rm_e500v2_loops_48 \
    gcc.fix_e5500-e6500-aeabi-multi-lib \
    gcc.fix_ivopts \
    gcc.sysroot_spec_only_linux \
    gcc.fix_extelim_gcc_6x \
    gcc.debug_md \
    gcc.optimize_static_vars \
    gcc.poison_dirs \
    gcc.vle_494 \
    gcc.vle_LSP_49x \
    gcc.easy_on_slow_tests \
    gcc.more_dejagnu_parallelization \
    gcc.fix_isel_49x \
    gcc.fix_trap_49x \
    gcc.rm_slow_tests_vle \
    gcc.vle_spe2 \
    gcc.vle_short_double"

# Patch Binutils
WORKDIR /src/binutils-$BINUTILS_VERSION
RUN bash -c 'for p in $BINUTILS_PATCHES; do patch -lbsf -p1 < /src/s32ds_patches/e200_compiler/binutils-$BINUTILS_VERSION/$p; done'

# Build binutils
WORKDIR /build/binutils
RUN /src/binutils-$BINUTILS_VERSION/configure \
    --target=${TARGET_ARCH} \
    --prefix=${TOOLCHAIN_PATH} \
    --disable-nls
RUN  make -j$(nproc) all
RUN  make install

# Patch GCC
WORKDIR /src/gcc-$GCC_VERSION
RUN find gcc/testsuite/gfortran.dg -type f -exec dos2unix {} \;
RUN bash -c 'for p in $GCC_PATCHES; do patch -lbsf -p1 < /src/s32ds_patches/e200_compiler/gcc-$GCC_VERSION/$p; done'

# Build gcc
WORKDIR /build/gcc

RUN /src/gcc-$GCC_VERSION/configure \
    --target=${TARGET_ARCH} \
    --prefix=${TOOLCHAIN_PATH} \
    --with-cpu=e200z0 \
    --disable-nls \
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
