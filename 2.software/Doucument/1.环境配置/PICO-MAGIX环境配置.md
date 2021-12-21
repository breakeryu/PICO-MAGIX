PICO-MAGIX环境配置

# 一、开发环境

## 环境下载配置

现在使用Arduino IDE来进行开发。具体的使用工具有下面的几个工具：

### 1.Arduino IDE

下载最新版。不要装在中文路径下面。安装JAVA等依赖。中文。

### 2.Vscode 

下载最新版。下载中文界面、C/C++插件等必要工具。

### 3.Vscode插件Arduino

![image-20211220152936659](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220152936659.png)

这里有个注意的地方：因为vscode插件其实还是使用arduinoIDE来进行编译工程的，所以这里还是要引用ArduinoIDE的路径，这里需要配置arduino的路径。我的路径配置如下：

![image-20211220161549363](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220161549363.png)

## 环境配置的问题

### 1. vscode的输出中文乱码

解决办法是：![image-20211220153016280](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220153016280.png)

参考了博客：https://blog.csdn.net/weixin_42225355/article/details/104906950

### 2.头文件包含问题

没有进行配置头文件路径的会出现下图的问题，头文件找不到：

![image-20211220153230122](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220153230122.png)

虽然现在没有什么好办法解决这个问题，但是他不影响我们编译、运行程序。这一点对于我们利用这个工具来说还是运气不错的，找了一个不差的工具。

### 3.文件夹创建方法

在写代码过程中，我们会将一类驱动放在一个文件夹中，使整个工程结构更加的清晰。

这里的环境同样可以创建相似的文件夹目录。具体的方法：

- 首先创建文件夹：这里我使用src文件夹做演示。

  ![image-20211220160753403](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220160753403.png)

- 接着，我们把led.cpp和led.h放在src文件夹中。
- 在要使用的文件中引用这个文件夹中的头文件![image-20211220160927433](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220160927433.png)

# 二、开发板环境配置

## Arduino IDE

1. 打开 Arduino IDE ， 文件->首选项.

2. 在“附加开发板管理器网址”中新启一行，添加:

    https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

   ![image-20211220163052489](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220163052489.png)

3. 点击OK关闭对话框.

4. 点击Tools->Boards->Board Manager in the IDE

   ![image-20211220163230961](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220163230961.png)

5. 搜索 “pico” ，select “Add”:

   ![image-20211220163332721](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220163332721.png)

## VS CODE

1.用VS CODE打开工程文件夹

2.配置板子型号：按下图来配置。

![image-20211220163637779](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220163637779.png)

## 引用我的库文件

### 1.LCD库

这里使用的硬件是ST7735，目前的接线是4线的SPI，如图所示：

![image-20211220210510621](C:\Users\iccad\AppData\Roaming\Typora\typora-user-images\image-20211220210510621.png)

现在我有一个问题是，现在看很多人写的代码中，是将DC（或者一般叫RS）引脚连接到普通的IO上，然后在初始化的时候将该IO拉高。并没有其他的使用DC引脚的地方。

那么我有一个问题是：能否直接将DC引脚直接拉高到3V3电平？LCD还能稳定工作吗？

**Q:**

**现在直接使用TFT_eSPI这个库，但是我想要自己做一些改变。现在的库只能够使用SPI0，他的做法现在是将初始化中的函数给赋值了spi0，没有对spi1的使用。**

**一定可以做出一个切换，这个切换可以任意的使用SPI接口来驱动LCD!**





### LAST Reference

参考了博客来进行C++的库的编写：

https://www.cnblogs.com/lulipro/p/6090407.html

