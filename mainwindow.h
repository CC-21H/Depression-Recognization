#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>

#include <QMainWindow>
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include <QValueAxis>
#include "chartview.h"
#include "callout.h"

#include <QValueAxis>
#include <QTimerEvent>
#include <QLineSeries>
#include <time.h>
#include <QWidget>
#include <QChartView>
#include <QGraphicsView>
#include <ActiveQt\QAxWidget>
#include <QAudioInput>
#include <QAudioOutput>
#include <iostream>
#include <QFile>
#include <QBuffer>
//#include <include/opencv2/core/core.hpp>
#include <include/opencv2/highgui/highgui.hpp>
#include <include/opencv2/opencv.hpp>
#include <include/opencv2/video.hpp>
#include <include/opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include<QtGui>
//using namespace cv;
using namespace std;


QT_CHARTS_USE_NAMESPACE
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void TempInferfaceInit(void);
    void TempInferfaceInit_2(void);
    void TempInferfaceInit_3(void);


    void addToPlaylist(const QStringList& fileNames);//视频部分

    string filenames;
    int video_time;

private slots:
    void Btn_Stop();
    void showPointData(QPointF position, bool isHovering);
    void SeriesInit(qint8 ch);
    void SeriesInit_2(qint8 ch);
    void SeriesInit_3(qint8 ch);


    //文字通道部分
    void pbtnClicked();

    //视频部分
    void play();//播放//test是曲线状态是否已经准备好

    //void handleError();//播放异常的抛出
    void on_toolButton_2_clicked();



    //视频离散接口部分
    //void receiveslot(float videoDiscrete);
    //音频离散接口部分
    //void receiveslot_2(float audioDiscrete);
    //多模态离散接口部分
    //void receiveslot_3(float multimodalDiscrete);

    //视频离散接口部分
    void receiveslot(vector<float> audioScoreVector);
    //音频离散接口部分
    void receiveslot_2(vector<float> videoScoreVector);
    //多模态离散接口部分
    void receiveslot_3(vector<float> multimodalScoreVector);



    //调用外部exe程序
    //void  slotVCR();


private:
    Ui::MainWindow *ui;

    //视频部分
    QMediaPlayer *mediaPlayer;
    void Init();

    //曲线部分
    QLineSeries *m_series[4];
    QLineSeries *m_series_2[4];
    QLineSeries *m_series_3[4];

    QChart *m_chart;
    QChart *m_chart_2;
    QChart *m_chart_3;

    QTimer *TempTime;
    QTimer *TempTime_2;
    QTimer *TempTime_3;

    QTimerEvent *event;
    bool isStopping;

    Callout *tip;
    Callout *tip_2;
    Callout *tip_3;

    QValueAxis *axisX;
    QValueAxis *axisY;
    QValueAxis *axisX_2;
    QValueAxis *axisY_2;
    QValueAxis *axisX_3;
    QValueAxis *axisY_3;

    QChartView *chartView;
    QChartView *chartView_2;
    QChartView *chartView_3;

    QMediaPlayer *pMediaPlayer;
    QMediaPlaylist *pMediaPlaylist;


    int m_timerId;

    qint8 currentChangel;
    qint8 currentChangel_2;

    float none = 0.203125;
    float mild = 0.296875;
    float moderate = 0.4375;
    float severe = 0.984375;

    float current_audioscore = 0;
    float current_videoscore = 0;
    float current_multimodalscore = 0;

    // 与坐标轴相关
    int xrange = 10;
    double yrange = 1;
    int xcount = 10;
    int ycount = 20;


    float scale = 1;  //数值放大倍数

};

#endif // MAINWINDOW_H
