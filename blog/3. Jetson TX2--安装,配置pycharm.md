## pycharm安装
TX2下anaconda是装不上的，但是pycharm还是可以装的，是一个很好用的IDE，PC端移植就用的是pycharm与spyder进行联合调试，一般习惯于用pycharm来写代码，因为它的代码补全功能简直要和VS媲美了，用spyder来调试，主要是查看数据比较方便。
TX2上用pycharm还是很简单的。安装的时候还是有一点坑的。

1. 下载pycharm社区版。
https://www.jetbrains.com/pycharm/download/#section=linux
2.  解压。
ubuntu可以直接使用右键解压，当然可以cd切换到目标所在目录使用tar -avxf来进行解压。
3. cd到bin文件夹，运行./pycharm.sh

到这一步如果可以顺利安装的话就恭喜了，我遇到的问题是缺少JDK环境。所以还需要解决这个问题。
关于这个问题需要安装JDK环境，我一开始按照下面的方法安装。

1. 去oracle官网下载,[链接点此](http://www.oracle.com/technetwork/cn/java/javase/downloads/jdk8-downloads-2133151-zhs.html)。也可以使用wget http://download.oracle.com/otn-pub/java/jdk/8u111-b14/jdk-8u111-linux-x64.tar.gz 安装包在你执行这个命令时所在的文件夹位置。
2. 解压 
`tar -zxvf jdk-8u111-linux-x64.tar.gz`
3. 移动到自己想放的位置：
`mkdir /usr/lib/jdk`    
`mv jdk1.8.0_111  /usr/lib/jdk/jdk1.8`
4. 设置环境变量：
方案一：修改全局配置文件，作用于所有用户：vim /etc/profile 
```
　　export JAVA_HOME=/usr/lib/jdk/jdk1.8
　　export JRE_HOME=${JAVA_HOME}/jre
　　export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib
　　export PATH=.:${JAVA_HOME}/bin:$PATH
 ```   
 方案二：修改当前用户配置文件，只作用于当前用户：vim ~/.bashrc 设置与上一样
5. 使修改的配置立刻生效：`source /etc/profile `或者 `source ~/.bashrc`
6. 检查是否安装成功：`java -version`

安装是成功了，jave-version也可以显示，这时候再返回去安装pycharm的时候出现另外一个问题： `Startup Error: Application cannot start in headless mode`,你可能不会遇到这个问题，那就非常恭喜。

解决方案可能有很多种，都在[这里](https://stackoverflow.com/questions/27727826/problems-installing-pycharm).
我的yum命令不能用，所以我把JDK环境重新装了一下，我好像不太记得怎么装的了，反正就是JDK环境的问题，然后返回去安装pycharm就可以了。

## pycharm配置。
其实配置也比较简单了，如果是可以装anaconda的话，那么直接配置anaconda的解释器就更简单了，这里面不行，但是可以使用其提供的virtualenv，这个可以提供一个虚拟的环境，也是很有好处的，比如我这个项目需要用python2，那么我就可以吧虚拟的解释器设置为python2，另外一个是3，那么久可以把解释器设置为python3，要选中inherit global site-packages,把一些外链的库也添加进来，opencv就应该属于这种。
然后新建项目就可以使用了。

![](https://upload-images.jianshu.io/upload_images/5252065-6e19be8f23347688.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/5252065-64f46dc537a724ad.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

然后就可以愉快的使用了，




