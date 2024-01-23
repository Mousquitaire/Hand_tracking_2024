#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <thread>
#include <vector>

#include <QThread>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class VideoThread: public QObject
{
    Q_OBJECT
public:
    VideoThread();
    ~VideoThread();
    bool IsRunning(){return isRunning;}
    void IsRunning(bool value){isRunning = value;}

public slots:
    void Run();

signals:
    void onFrameCaptured(Mat& frame);
    void finished();
    void error(QString err);

private:
    bool isRunning;

};

#endif // VIDEOTHREAD_H
