YOLOv3的论文我还没看，不过早闻大名，这个模型应该是现在目标检测领域能够顾全精度和精度的最好的模型之一，模型在高端单片显卡就可以跑到实时（30fps）的帧率（1080p视频），而且这个模型有依赖opencv的版本，且有训练好的模型参数使用，也是在jkjung的博客上看到实现过程，所以来试一下，总的来说还是比较顺利的，很快就得到了结果。

#### [YoloV3官网](https://pjreddie.com/darknet/yolo/)
linux系统下使用可能比较方便，我原先试过在win10+VS2015+opencv3.4的环境下试过编译，但是未能成功，不太清楚是什么原因。
#### [YoloV3在TX2上跑起来](https://jkjung-avt.github.io/yolov3/)
这个博客写的很清楚，按照这个做下来就可以了，要求已经配置opencv+cuda环境，这个配置可以参考他的另外一个博客，我在[这里](https://www.jianshu.com/p/ae7185d26780)也整理了。

#### Note
我的网速非常不行，下载weights的速度只有几十k，所以特别慢，拖同学下载了再拿网盘传过来才好点，网盘链接放在下面，如有需要，可以下载。
[YoloV3_weights](https://pan.baidu.com/s/1P2tWBRYEF4mcvGatJOZv1Q)  百度网盘。

效果图我也不放了，拿手机站在楼上拍了一段，1080的视频，大概能跑到3-3.4fps的速度，毕竟GPU只有256个核。
