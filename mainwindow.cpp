#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<Mat>("Mat&");

    // UI Setup

    ui->setupUi(this);

    this->setWindowTitle("Hand Tracking");

    QPushButton* captureButton = ui->captureButton;
    connect(captureButton, &QPushButton::released, this, &MainWindow::ToggleVideoCapture);
}

void MainWindow::ToggleVideoCapture()
{
    isCameraActive = !isCameraActive;

    if(!isCameraActive)
    {
        StopVideoCapture();
    }
    else
    {
        ui->captureButton->setText("Stop Camera");
        StartVideoCapture();
    }
}

void MainWindow::StartVideoCapture()
{
    // Handle Video Capture Thread
    thread = new QThread(this);
    videoThread = new VideoThread();

    videoThread->moveToThread(thread);

    connect( videoThread, &VideoThread::error, this, &MainWindow::CaptureError);
    connect( videoThread, &VideoThread::onFrameCaptured, this, &MainWindow::OnFrameCaptured);
    connect( thread, &QThread::started, videoThread, &VideoThread::Run);
    connect( videoThread, &VideoThread::finished, thread, &QThread::quit);
    connect( videoThread, &VideoThread::finished, videoThread, &VideoThread::deleteLater);
    connect( thread, &QThread::finished, thread, &QThread::deleteLater);
    connect( thread, &QThread::finished, this, &MainWindow::ClearVideoPixmap);
    thread->start();
}

void MainWindow::StopVideoCapture(){
    videoThread->IsRunning(false);
    isCameraActive = false;
}

void MainWindow::OnFrameCaptured(const cv::Mat &frame)
{
    QImage imgIn = convertOpenCVMatToQtQImage(frame);

    ui->lblVideo->setPixmap(QPixmap::fromImage(imgIn));
}

void MainWindow::ClearVideoPixmap()
{
    ui->lblVideo->setPixmap(QPixmap());
    ui->lblVideo->repaint();
    ui->captureButton->setText("Start Camera");
    ui->lblVideo->setText("Waiting for video device...");
}

MainWindow::~MainWindow()
{
    videoThread->IsRunning(false);
    delete ui;
}

QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat)
{
    if(mat.channels() == 1) { // if 1 channel (grayscale or black and white) image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);// return QImage
    }
    else if(mat.channels() == 3) { // if 3 channel color image
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);// flip colors
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);// return QImage
    }
    else {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage();// return a blank QImage if the above did not work
}

void MainWindow::CaptureError(QString err)
{
    isCameraActive = false;
    ui->captureButton->setText("Start Camera");
    ui->lblVideo->setText("Capture device not found");
}

