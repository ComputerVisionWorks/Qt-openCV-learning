### linux 下opencv环境搭建
直接终端安装：

    $➜  ~ sudo apt-get install libopencv-dev   

如果还没有安装pkg-config的，先安装：

    $-> ~ sudo apt-get install pkg-config

在qt 工程文件添加：

    PKGCONFIG += opencv
    CONFIG += c++11 link_pkgconfig

helloworld程序:

```c++
#include "widget.h"
#include <QApplication>
#include "opencv2/opencv.hpp"
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VideoCapture capture(0);
    while(1){
        Mat frame;
        capture>>frame;
        imshow("hello world",frame);
        waitKey(10);
    }
    return 0;
}
```

截图：

![a](../../imgs/helloworld.png)
