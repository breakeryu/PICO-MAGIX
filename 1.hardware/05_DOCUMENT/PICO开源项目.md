PICO开源项目



# 一、环境构建

## 1.环境

现在使用PIO很难搞成功。使用arduino原生的IDE可以编译。接下来就用原生的IDE来编辑吧。

## 2.上传

问题中显示了部分上传的方式。

https://community.platformio.org/t/official-platformio-arduino-ide-support-for-the-raspberry-pi-pico-is-now-available/20792/9

## 3.项目开源地址

https://github.com/breakeryu/PICO-MAGIX

# 二、系统设计

## 1.子系统——环境传感器部分

环境传感器部分采用了几个部分：

AHT21B温湿度模块

VL6180X距离模块

st7735显示模块

MQ135气体检测模块

temt6000环境光模块

这样构成了一个环境的检测系统。

### 子系统功能：

该环境监测系统可以进行数据采集，显示。可以设置报警值。

使用QT设计一个上位机，可以使数据可视化，并且可以保存到本地。



## 2.车门/灯状态机系统

这一部分使用状态机测试的code，来模拟一个汽车车门和车灯控制器：

- 车门+车门灯

- 车内头氛围灯（开/关）+ 开关（单刀开关）

- 锁止机构（可以锁各个门，按下之后禁止开门）（单刀开关）

- 车钥匙开门（单刀开关）

- 车门开门（单刀开关）

  

### 子系统功能：

我们需要8个开关，然后是5个灯。

这样一个车门和灯配合的控制系统，在普通的汽车上面都是常见的。

现在我们使用LED和一些开关按键来模拟这个系统。



## 3.语音识别系统

使用启英泰伦的开源硬件。参考一个开源的灯项目，来集成到我的板卡上面。

# 三、硬件设计

硬件设计开源：在[开源仓库](https://github.com/breakeryu/PICO-MAGIX)中的[1.hardware](https://github.com/breakeryu/PICO-MAGIX/tree/master/1.hardware)部分。

硬件设计使用工具是AD19。原理图和PCB会生成PDF版本。

# 四、软件设计



# 六、项目依赖

使用Arduino平台，集成开发环境使用vscode和pio。

这里是我的主要代码参考文档：https://arduino-pico.readthedocs.io/en/latest/

使用的项目原来的git工程：https://github.com/earlephilhower/arduino-pico