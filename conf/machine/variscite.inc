INHERIT += "image-buildinfo"

MACHINE_FEATURES += " pci bluetooth wifi"

IMX_DEFAULT_BSP = "nxp"

USE_VT = "0"

KERNEL_IMAGETYPE_mx8 = "Image.gz"

WKS_FILE_mx8 = "imx-imx-boot-singlepart.wks.in"

DEFAULTTUNE_mx8mm  ?= "cortexa53-crypto"
DEFAULTTUNE_mx8mn  ?= "cortexa53-crypto"
DEFAULTTUNE_mx8mq  ?= "cortexa53-crypto"
DEFAULTTUNE_mx8qxp ?= "cortexa35-crypto"
DEFAULTTUNE_mx8qm ?= "cortexa72-cortexa53-crypto"

# Variscite BSP default providers
PREFERRED_RPROVIDER_u-boot-default-env ?= "u-boot-variscite"

# Use i.MX Gstreamer Version
MACHINE_GSTREAMER_1_0_PLUGIN_mx8 = "imx-gst1.0-plugin"
PREFERRED_VERSION_imx-gst1.0-plugin_mx8 ?= "4.6.1"
PREFERRED_VERSION_gstreamer1.0_mx8              ?= "1.18.0.imx"
PREFERRED_VERSION_gstreamer1.0-plugins-base_mx8 ?= "1.18.0.imx"
PREFERRED_VERSION_gstreamer1.0-plugins-good_mx8 ?= "1.18.0.imx"
PREFERRED_VERSION_gstreamer1.0-plugins-bad_mx8  ?= "1.18.0.imx"
PREFERRED_VERSION_gstreamer1.0-plugins-ugly_mx8 ?= "1.18.0"
PREFERRED_VERSION_gstreamer1.0-libav_mx8        ?= "1.18.0"
PREFERRED_VERSION_gstreamer1.0-rtsp-server_mx8  ?= "1.18.0"

# Add VPU and Cortex M4/M7 firmware
MACHINE_FIRMWARE_append_mx8 = " \
	firmware-imx-vpu-imx8 \
	freertos-variscite \
	"

# Add VPU and Cortex M4/M7 firmware
MACHINE_FIRMWARE_append_mx8 = " \
	freertos-variscite \
	"
MACHINE_EXTRA_RDEPENDS += " \
	gptfdisk \
	hostapd \
	hdparm \
	imx-kobs \
	iw \
	kernel-modules \
	kmod \
	${@bb.utils.contains('DISTRO', 'b2qt', '', \
           bb.utils.contains('DISTRO_FEATURES', 'wayland', 'networkmanager networkmanager-nmcli', \
                                                       '', d), d)} \
	packagegroup-tools-bluetooth \
	bluez-alsa \
	pm-utils \
	rng-tools \
	wpa-supplicant \
	wireless-regdb-static \
	u-boot-fw-utils \
	u-boot-splash \
"

# Packages added to all images (including core-image-minimal)
IMAGE_INSTALL_append_mx8 = " \
	kernel-image \
	kernel-devicetree \
"

IMAGE_FSTYPES = "tar.gz wic.gz"

# Wayland based distros add systemd to DISTRO_FEATURES
# Remove sysvinit or systemd based on DISTRO_FEATURES to avoid conflicts
DISTRO_FEATURES_BACKFILL_CONSIDERED_append = "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', ' sysvinit', '', d)}"
DISTRO_FEATURES_BACKFILL_CONSIDERED_append = "${@bb.utils.contains('DISTRO_FEATURES', 'sysvinit', ' systemd', '', d)}"

# Use bluez-alsa instead of pulseaudio
DISTRO_FEATURES_BACKFILL_CONSIDERED_append = " pulseaudio"
