# 1.PICO_MAGIX介绍
什么是PICO_MAGIX呢？
它是一款开源硬件，也是个使用Arduino的开源软件，后续会增加QT应用的一个开源代码仓库。

# 2.Hardware
硬件板卡使用了Altium Designer来设计。工程结构如下：

--hardware文件目录

* * *

--01_SCH        （存放工程的原理图文件）

--02_PCB        （存放工程的PCB文件）

--03_LIB         （存放工程的原理图库和PCB库文件）

--04_DATESHEET      （存放工程使用的数据手册）

--05-DOCUMENT     （存放工程导出的文件和bom等）

--06_PRODUCT        （存放工程的制版信息）

--PICO顶层工程          （使用AD软件打开的工程文件）

# 3.Software


软件使用Arduino IDE来进行编写，主要使用C和C++语言。

工程包括一个单元测试工程和项目发布工程。

目前正在编写单元测试工程。
