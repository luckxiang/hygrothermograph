# hygrothermograph
温湿度计,帮兄弟女票随手做的毕设作品,据说拿了个优秀,专业第五      
硬件配置:STC12C5A60S2最小系统板+DHT11温湿度传感器+1.44寸TFT液晶彩屏      
实现很简单,设计加上编码不到半个小时.不过由于DHT11源码是基于52单片机的,移植到STC12总线时序有点问题,花了一个多小时调试.        
优化的话可以再加一个时钟芯片,偷懒弄了一个定时器替代.            
![实物图](http://7xs8go.com1.z0.glb.clouddn.com/hygrothermograph.jpeg)
