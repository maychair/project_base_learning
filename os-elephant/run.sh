#!/bin/bash 
echo -e "\033[31m========================== env check  ================================================== \033[0m"
if [ ! -e bochsrc.disk ];then 
    echo "no bochsrc.disk,please checkout!"
    exit 1
fi
if [ ! -e hd3M.img ];then 
    echo "no bootimage!"
    exit 1
fi
if [ ! -e  /usr/local/bochs/share/bochs/keymaps/x11-pc-us.map ];then
    echo "/usr/local/bochs/share/bochs/keymaps/x11-pc-us.map does not exist..."
    exit 1
else
    file /usr/local/bochs/share/bochs/keymaps/x11-pc-us.map
fi

if [ ! -e  /usr/local/bochs/share/bochs/BIOS-bochs-latest ];then
    echo " /usr/local/bochs/share/bochs/BIOS-bochs-latest does not exist..."
    exit 1
else 
    file /usr/local/bochs/share/bochs/BIOS-bochs-latest
fi

if [ ! -e  /usr/local/bochs/share/vgabios/vgabios.bin ];then
    echo "/usr/local/bochs/share/vgabios/vgabios.bin does not exist..."
    exit 1
else
    file /usr/local/bochs/share/vgabios/vgabios.bin
fi
echo -e "\033[31m========================== check over ================================================== \033[0m"
echo -e "\033[31m==========================   run      ================================================== \033[0m"
/usr/local/bochs/bin/bochs -f bochsrc.disk
