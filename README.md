# STm32 T-motor AK80-8 示例代码 #

使用STM32F429驱动，CAN ID为1，CAN波特率为1Mbps

HAL Version: V1.8.1 / 24-June-2022

ARM Clang 6.21，可以在ARM CC 5.06下编译通过

## 上位机使用 ##

感谢[Nikodem Bartnik](https://github.com/NikodemBartnik)提供的Python代码

确保电脑安装了Python3及以上，且装好了串口驱动

将STM32F429的串口1通过USB to TTL连接到电脑，然后给电机和单片机上电

打开终端运行以下命令：

```
pip install -r requirements.txt
python serial_com.py
```