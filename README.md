### BBC 
分为几个模块：
* lexer: 代码到token
* parser: token到ast
* codegen: ast到汇编
* assembler: 汇编到bin

少了一个优化模块，没有生成四元表达式做优化。

codegen时主要有两个问题：
* 局部变量相对rb的偏移如何存储
* 拿到operation时的参数的类型


#### v0.0.1
* 只支持int类型的变量类型
  
* 支持基本的四则运算

* 支持如下语句
  * PRINT 
  * IF
  * WHILE
  * DIM
  * GOTO
  
#### TODO
- [x] 生成ASM
- [x] 生成二进制
- [x] Expression表达式返回值类型确定
- [x] 完成PRINT语句
- [x] 实现关系运算符
- [ ] 实现多数据类型
- [ ] 实现数组
- [ ] 实现输入
    
    
### BBVM

一开始写VM的时候，可能因为之前写模拟器的习惯，是按照CPU/GPU/Keyboard等

为了方便移植，对各个模块进行了抽象。在桌面端使用sdl
bbvm: 虚拟机核心，执行opcode，与平台无关
input: 键盘和屏幕监听
renderer: 渲染器，负责绘制画面
screen: 显示器，负责输出画面
storage: 存储模拟器

对于一般的机器，renderer会将绘制好的数据放到缓存中，然后显示器会定期

Android版本BBasic:
* vmsurface相当于screen，开了一个线程定期绘制vmsurface。
几个问题：
  1. input_str：每输入一个字符就刷新一次界面。如果消息机制放在主线程，



#### v0.1
基本能Run起来了，功能也基本完善。但是架构上还有一些优化的地方，整个架构不是异步以及事件驱动。
* 渲染器和显示器没有做到解耦，接口没有定义得特别清晰。
* 事件循环机制待优化，目前是固定的40ms接收一次事件。
* 显示器不支持放大缩小。
* 帧数控制。


#### TODO
* 同步渲染和绘制（异步？）
* 按键事件优化(异步，接受事件, 防止阻塞)