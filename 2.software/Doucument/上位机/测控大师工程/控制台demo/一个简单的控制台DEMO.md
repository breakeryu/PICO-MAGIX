一个简单的控制台DEMO

# 一、DEMO说明

我们从这个教程中能够练习以下几个格西测控大师的使用方法：

1. 简单控件使用
2. 事件脚本的编写
3. 自定义序列命令
4. 串口设备的使用

# 二、开始吧

## 1.创建一个画面



在画面中，使用了自定义的画布，使用了按键和开关控件。

## 2.创建一个设备和接口

这里的命名为默认名字,串口。

# 三、在脚本中执行步骤的几种方式

## 1.使用步骤的ID名

`Context.StartStep("82BCBA44-AD16-4214-BA0F-AD6D7E3BFC9A");`

## 2.使用步骤所处的序列位置

`Context.StartStep("控制台测试序列/写LED系统状态1");`

## 3.使用变量

`Context.StartStep(Context.Variants["步骤名/LED写1"].ToString());`

# 四、数据绑定

