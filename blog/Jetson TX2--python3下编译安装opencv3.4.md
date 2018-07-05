jetpack3.2自带了opencv3.3，但是只提供了python2.7的编译版本，所以也只能在python2.7下使用，我本来以为有什么更简单的方法链接到python3中，但是遍查资料也没人说过这个东西，直到我找到一篇博客。
[how to install opencv3.4.0 on jeson TX2](https://jkjung-avt.github.io/opencv3-on-tx2/)
这片文章写得非常好，把刷完机后所有的准备工作都写得很清楚，包括如何卸载旧的opencv版本。我就不重新写一遍了，只说下大概可能遇到的问题。

#### 1. 安装matplotlib出错。 
前面卸载安装一些东西都很顺利，直到安装matplotlib的时候会报错（如果没有报错就不用管了），原因是需要一些预装库python3-tk。nose库。所以按照下面的命令依次安装就可以了。

```python
sudo apt-get install python3-tk
pip3 install nose
pip3 install pillow
pip3 install spicy
pip3 install matplotlib
```
#### 2. 下载时网速很慢。
这个主要是下载opencv的时候很慢，还有个什么下载也很慢，我的解决方法就是换了手机热点，然后网速嗖嗖的，基本上解决了，移动4g，联通电信不太清楚，我用的是校园网，所以可能有这个问题，如果是其他的网络的话可能就没有问题。
#### 3. 修改cuda_gl_interop.h
教程里的是通过vim进去的，对vim很熟的就不说了，先进入insert模式然后再推出，输入冒号：，输入wq保存退出，实际上就是给那几行加了注释。
#### 4. 对照一下General configuration for OpenCV 3.4.0。
对照一下这个信息保证正确，如果不对的话就回去查看下cmake时候输入的配置信息。

这样应该就没有什么问题了，python2和python3都安装上了opencv，可以愉快的使用了。


