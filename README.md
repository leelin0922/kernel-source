Examples:copy git source from yocto git source    

cp -arf ~/fsl-release-bsp/build-x11/tmp/work-shared/imx6dlsabresd/kernel-source SBC-7112S_Linux_Kernel-v4.9.11    
cd SBC-7112S_Linux_Kernel-v4.9.11   
git remote add SBC-7112S_Linux_Kernel-v4.9.11 https://github.com/leelin0922/kernel-source.git   
git fetch https://github.com/leelin0922/kernel-source.git   
git checkout -b SBC-7112S_Linux_Kernel-v4.9.11    
git push SBC-7112S_Linux_Kernel-v4.9.11 SBC-7112S_Linux_Kernel-v4.9.11    

Examples:copy git commit git clone https://github.com/leelin0922/u-boot.git -b SBC-7112S_Linux_Uboot-v2017.03   

git status    
git add .   
git commit    
