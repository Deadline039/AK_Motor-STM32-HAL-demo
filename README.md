# STm32 T-motor AK80-8 示例代码 #

使用STM32F429驱动，CAN ID为1，CAN波特率为1Mbps

HAL Version: V1.8.1 / 24-June-2022

ARM Clang 6.21，可以在ARM CC 5.06下编译通过

## 上位机使用 ##

感谢[Nikodem Bartnik](https://github.com/NikodemBartnik)提供的Python代码

确保电脑安装了Python3及以上，且装好了串口驱动

将STM32F429的串口1通过USB to TTL连接到电脑，然后给电机和单片机上电

打开终端运行以下命令安装依赖：

```
pip install -r requirements.txt
```

输入以下命令打开上位机

```
python serial_com.py
```

选择正确的COM口，点Connect连接，Set Origin可以将当前位置设为原点。

拖动Trackbar就可以直接让电机运动。Position可以让电机转角度，Speed可以以指定速度旋转，Current可以作为扭矩使用。具体参考代码注释。

<img src="./assets/Snipaste_2023-11-28_16-44-53.png" style="zoom:67%;" />

