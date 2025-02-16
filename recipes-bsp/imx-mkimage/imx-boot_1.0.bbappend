# Copyright (C) 2017-2020 NXP
# Copyright (C) 2021 Variscite LTD

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

require imx-mkimage_git.inc

SRC_URI_append_imx8mn-var-som = " file://imx-mkimage-imx8m-soc.mak-add-var-som-imx8m-nano-support.patch"
SRC_URI_append_imx8mq-var-dart = " file://imx-mkimage-imx8m-soc.mak-add-dart-mx8m-support.patch"
SRC_URI_append_imx8mm-var-dart = " file://imx-mkimage-imx8m-soc.mak-add-variscite-imx8mm-suppo.patch"
SRC_URI_append_imx8mp-var-dart = " file://imx-mkimage-imx8m-soc.mak-add-dart-mx8mp-support.patch"

do_compile() {
    echo "Copying DTBs"
    if [ -f ${DEPLOY_DIR_IMAGE}/${BOOT_TOOLS}/imx8mm-var-som-symphony.dtb ]; then
        cp ${DEPLOY_DIR_IMAGE}/${BOOT_TOOLS}/imx8mm-var-som-symphony.dtb ${S}/iMX8M/
    fi

    if [ -f ${DEPLOY_DIR_IMAGE}/${BOOT_TOOLS}/imx8mp-var-dart-dt8mcustomboard-legacy.dtb ]; then
        cp ${DEPLOY_DIR_IMAGE}/${BOOT_TOOLS}/imx8mp-var-dart-dt8mcustomboard-legacy.dtb ${S}/iMX8M/
    fi

    if [ -f ${DEPLOY_DIR_IMAGE}/${BOOT_TOOLS}/imx8mp-var-som-symphony.dtb ]; then
        cp ${DEPLOY_DIR_IMAGE}/${BOOT_TOOLS}/imx8mp-var-som-symphony.dtb ${S}/iMX8M/
    fi

    # mkimage for i.MX8
    # Copy TEE binary to SoC target folder to mkimage
    if ${DEPLOY_OPTEE}; then
        cp ${DEPLOY_DIR_IMAGE}/tee.bin ${BOOT_STAGING}
    fi
    for target in ${IMXBOOT_TARGETS}; do
        compile_${SOC_FAMILY}
        if [ "$target" = "flash_linux_m4_no_v2x" ]; then
           # Special target build for i.MX 8DXL with V2X off
           bbnote "building ${IMX_BOOT_SOC_TARGET} - ${REV_OPTION} V2X=NO ${target}"
           make SOC=${IMX_BOOT_SOC_TARGET} ${REV_OPTION} V2X=NO dtbs="${UBOOT_DTB_NAME} ${UBOOT_DTB_EXTRA}" flash_linux_m4
        else
           bbnote "building ${IMX_BOOT_SOC_TARGET} - ${REV_OPTION} ${target}"
           make SOC=${IMX_BOOT_SOC_TARGET} ${REV_OPTION} dtbs="${UBOOT_DTB_NAME} ${UBOOT_DTB_EXTRA}" ${target}
        fi
        if [ -e "${BOOT_STAGING}/flash.bin" ]; then
            cp ${BOOT_STAGING}/flash.bin ${S}/${BOOT_CONFIG_MACHINE}-${target}
        fi
    done
}
