#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "videothread.h"

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImage convertOpenCVMatToQtQImage(cv::Mat mat);
    void OnFrameCaptured(const cv::Mat &frame);
    void ClearVideoPixmap();

    void StartVideoCapture();
    void StopVideoCapture();

private slots:
    void ToggleVideoCapture();

private:
    Ui::MainWindow *ui;
    void CaptureError(QString err);

    QThread* thread;
    VideoThread* videoThread;

    bool isCameraActive = false;
};
#endif // MAINWINDOW_H
