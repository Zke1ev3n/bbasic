### BBC 

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
* 生成ASM[]
    
    
### BBVM

一开始写VM的时候，可能因为之前写模拟器的习惯，是按照CPU/GPU/Keyboard等

为了方便移植，对各个模块进行了抽象。在桌面端使用sdl
bbvm: 虚拟机核心，执行opcode，与平台无关
input: 键盘和屏幕监听
renderer: 渲染器，负责绘制画面
screen: 显示器，负责输出画面
storage: 存储模拟器


#### v0.1
功能基本完善



#### TODO
* 同步渲染和绘制（异步？）
* 按键事件优化(异步，接受事件, 防止阻塞)