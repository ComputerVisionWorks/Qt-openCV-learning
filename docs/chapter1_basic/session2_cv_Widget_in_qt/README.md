#### 设计一个可复用的视频获取类
考虑到后面的例程也会复用同一个功能，在这里就设计一个可复用的视频获取类来作为学习

cvvideo.h

```c++
#ifndef CVVIDEO_H
#define CVVIDEO_H

#include <QObject>
#include <QThread>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

class CVVideo : public QThread
{
    Q_OBJECT
public:
    explicit CVVideo(QObject *parent = 0);

signals:
    void frameChanged(const Mat& frame);

public slots:

protected:
    void run();

};

#endif // CVVIDEO_H
```

cvvideo.cpp

```c++

#include "cvvideo.h"
#include <QDebug>

CVVideo::CVVideo(QObject *parent) : QThread(parent)
{
    qRegisterMetaType<Mat>("Mat");
    start();
}

void CVVideo::run()
{
    VideoCapture capture(0);
    while(1){
        Mat frame ;
        capture>>frame;
        Mat colorizedFrame;
        cvtColor(frame,colorizedFrame,CV_BGR2RGB);
        emit frameChanged(colorizedFrame);
        QThread::msleep(50);
    }
}

```

这个类继承了QThread，为了在Qt上使用的时候不阻塞主线程，继承QThread类来异步抓取视频流数据，等抓取完毕了就发信号更新一帧图像资源。

### 转换到QImage
Mat 对象默认获得的格式是BGR
所以我们需要用opencv自带的转换函数　：cvtColor(Mat source, Mat dst, ColorCOde)来转换成QImage正常读取的数据RGB格式。

```c++
Mat frame ;
capture>>frame;
Mat colorizedFrame;
cvtColor(frame,colorizedFrame,CV_BGR2RGB);
```

QImage初始化：

```c++
QImage img(frame.data,
  frame.size().width,
  frame.size().height,
  QImage::Format_RGB888);
```
好啦，转换完成，这样整个Mat对象的数据就可以正常在Qt控件中显示了！是不是很简单？
当然要深入了解整个函数的使用还有opencv所支持的格式转换就需要自行去官网文档查看了！这里就不一一列出来了。
