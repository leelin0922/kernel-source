. /opt/fsl-imx-x11/4.9.88-2.0.0/environment-setup-cortexa7hf-neon-poky-linux-gnueabi
#!/bin/sh

#echo $PATH
#echo $CROSS_COMPILE
#export CROSS_COMPILE=/opt/fsl-imx-fb/4.1.15/environment-setup-cortexa9hf-vfp-neon-pokylinux-gnueabi
#export CROSS_COMPILE=/opt/fsl-imx-fb/4.1.15/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-
#echo $PATH
#echo $CROSS_COMPILE
#outputdir="/mnt/hgfs/dshare/7112/i.mx6ul/mfgtools_for_6UL_20180806/mfgtools_for_6UL/Profiles/Linux/OS Firmware/files/linux/"
outputdir="/mnt/hgfs/dshare/7119/outputimage/"
export ARCH=arm

#make distclean
#make clean
make imx_v7_defconfig
#make 
make -j2
echo "zImage imx6ul-14x14-evk_emmc.dtb"
cp arch/arm/boot/zImage "$outputdir"zImage
cp arch/arm/boot/dts/imx6ul-14x14-evk-emmc.dtb "$outputdir"imx6ul-14x14-evk_emmc.dtb
cp arch/arm/boot/zImage /tftpboot/zImage
cp arch/arm/boot/dts/imx6ul-14x14-evk-emmc.dtb /tftpboot/imx6ul-14x14-evk_emmc.dtb
sync
sleep 1
echo "sync(:"
date
