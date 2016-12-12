Summary: u-boot version git-r33
Name: u-boot
Version: git
Release: r33
License: GPLv2
Group: bootloaders
Packager: Freescale Yocto Team <yocto@linux.freescale.net>
URL: http://u-boot.sf.net
BuildRequires: virtual/powerpc-fsl_networking-linux-gnuspe-gcc
BuildRequires: libgcc
BuildRequires: boot-format-native

%description
U-boot bootloader

%package -n u-boot-dbg
Summary: u-boot version git-r33 - Debugging files
Group: devel
Suggests: u-boot = git-r33

%description -n u-boot-dbg
U-boot bootloader  This package contains ELF symbols and related sources
for debugging purposes.

%package -n u-boot-staticdev
Summary: u-boot version git-r33 - Development files (Static Libraries)
Group: devel
Requires: u-boot-dev = git-r33

%description -n u-boot-staticdev
U-boot bootloader  This package contains static libraries for software
development.

%package -n u-boot-dev
Summary: u-boot version git-r33 - Development files
Group: devel
Requires: u-boot = git-r33
Suggests: libgcc-s-dev

%description -n u-boot-dev
U-boot bootloader  This package contains symbolic links, header files, and
related items necessary for software development.

%package -n u-boot-doc
Summary: u-boot version git-r33 - Documentation files
Group: doc

%description -n u-boot-doc
U-boot bootloader  This package contains documentation.

%package -n u-boot-locale
Summary: u-boot version git-r33
Group: bootloaders

%description -n u-boot-locale
U-boot bootloader

%package -n u-boot-images
Summary: u-boot version git-r33
Group: bootloaders

%description -n u-boot-images
U-boot bootloader

%files
%defattr(-,-,-,-)

%files -n u-boot-dbg
%defattr(-,-,-,-)

%files -n u-boot-dev
%defattr(-,-,-,-)

%files -n u-boot-images
%defattr(-,-,-,-)
%dir "/boot"
"/boot/u-boot-P2020RDB-PC-git-r33.bin"
"/boot/u-boot-nand-P2020RDB-PC_36BIT_NAND-git-r33.bin"
"/boot/u-boot-sd.bin"
"/boot/u-boot-spi-P2020RDB-PC_SPIFLASH-git-r33.bin"
"/boot/u-boot-spi.bin"
"/boot/u-boot.bin"
"/boot/u-boot-P2020RDB-PC_36BIT-git-r33.bin"
"/boot/u-boot-sd-P2020RDB-PC_36BIT_SDCARD-git-r33.bin"
"/boot/u-boot-spi-P2020RDB-PC_36BIT_SPIFLASH-git-r33.bin"
"/boot/u-boot-nand.bin"
"/boot/u-boot-sd-P2020RDB-PC_SDCARD-git-r33.bin"
"/boot/u-boot-nand-P2020RDB-PC_NAND-git-r33.bin"

