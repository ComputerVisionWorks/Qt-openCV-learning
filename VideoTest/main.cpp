#include <QApplication>
#include "../Widgets/abstractcvvideowidget.h"
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AbstractCVVideoWidget w;
    w.show();

    return a.exec();
}
