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

按照一个模拟器的实现，分别实现了cpu/gpu/keyboard/screen等部分，但是BB虚拟机并不是真的硬件，所以理论上也没有包含这几个部分，只是

#### v0.1
功能基本完善



#### TODO
* 同步渲染和绘制（异步？）
* 按键事件优化(异步，接受事件, 防止阻塞)