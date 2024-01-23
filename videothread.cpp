#include "videothread.h"

VideoThread::VideoThread(){}

VideoThread::~VideoThread(){}

void VideoThread::VideoThread::Run()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        emit error("Cannot open camera");
        return;
    }

    // Inside loop.
    Mat frame;

    isRunning = true;

    while(VideoThread::isRunning) {
        cap >> frame;

        emit onFrameCaptured(frame);

        if (waitKey(30) >= 0) {
            break;
        }
    }

    cout<<"Closing camera capture"<<endl;
    cap.release();
    emit finished();
};
