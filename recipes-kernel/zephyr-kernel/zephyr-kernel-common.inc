# Common settings for all Zephyr recipes

inherit zephyr

# There shouldn't be a manifest for zephyr kernels since there is no root
# filesystem.
IMAGE_NO_MANIFEST = "1"

ZEPHYR_MAKE_ARGS = " V=1 BOARD=${BOARD} CROSS_COMPILE=${CROSS_COMPILE} ZEPHYR_GCC_VARIANT="yocto" ZEPHYR_BASE=${ZEPHYR_BASE} SYSROOT=${STAGING_DIR_TARGET}"

# We always need a toolchain to cross-compile.
INHIBIT_DEFAULT_DEPS = "1"
DEPENDS += "gcc-cross-${TARGET_ARCH} libgcc"
CROSS_COMPILE = "${STAGING_BINDIR_TOOLCHAIN}/${TARGET_PREFIX}"

do_configure[noexec] = "1"

# The makefiles are explicit about the flags they want, so don't unset
# them so zephyr flags actually get used.
# This is done here rather than in the task so that things still work
# in devshell.

python () {
    d.delVar('CFLAGS')
    d.delVar('CXXFLAGS')
    d.delVar('LDFLAGS')
}
OE_TERMINAL_EXPORTS += "CROSS_COMPILE"
OE_TERMINAL_EXPORTS += "BOARD"
OE_TERMINAL_EXPORTS += "ZEPHYR_SRC_DIR"
OE_TERMINAL_EXPORTS += "ZEPHYR_BASE"