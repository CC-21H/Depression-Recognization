#include "mainwindow.h"
#include "dealthread.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>

#include<QPixmap>
#include<QFrame>
#include<QHBoxLayout>
#include<QFileDialog>
#include<QString>
#include<QGraphicsLayout>
#include <QAxWidget>
#include <QTimer>

#include <QAudioDeviceInfo>
#include <QMessageBox>
//extern "C"
//{
////    #include <ffmpeg/dev/include/libavcodec/avcodec.h>
////    #include <ffmpeg/dev/include/libavformat/avformat.h>
////    #include <ffmpeg/dev/include/libswscale/swscale.h>
////    #include <ffmpeg/dev/include/libavdevice/avdevice.h>
////    #include <ffmpeg/dev/include/libavformat/version.h>
////    #include <ffmpeg/dev/include/libavutil/time.h>
////    #include <ffmpeg/dev/include/libavutil/mathematics.h>
//    #include <libavcodec/avcodec.h>
//    #include <libavformat/avformat.h>
//    #include <libswscale/swscale.h>
//    #include <libavdevice/avdevice.h>
//    #include <libavformat/version.h>
//    #include <libavutil/time.h>
//    #include <libavutil/mathematics.h>
//}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),

    m_chart(new QChart),
    m_chart_2(new QChart),
    m_chart_3(new QChart),

    TempTime(new QTimer),
    TempTime_2(new QTimer),
    TempTime_3(new QTimer),

    isStopping(false),

    currentChangel(8) //可修改开始显示曲线条数2019.3.9
{
    ui->setupUi(this);
    //ui->widget->setAspectRatioMode(Qt::IgnoreAspectRatio);

    TempInferfaceInit(); // 建轴
    TempInferfaceInit_2();
    TempInferfaceInit_3();

    TempTime->setInterval(1000);//控制曲线速度
    TempTime_2->setInterval(1000); // 没用
    TempTime_3->setInterval(1000);

    tip = 0;
    tip_2 = 0;
    tip_3 = 0;

    connect(TempTime, SIGNAL(timeout()), this, SLOT(receiveslot()));//取消曲线动态替换
    connect(TempTime_2, SIGNAL(timeout()), this, SLOT(receiveslot_2()));
    connect(TempTime_3, SIGNAL(timeout()), this, SLOT(receiveslot_3()));

    //connect(ui->toolButton, SIGNAL(clicked(bool)), this, SLOT(on_toolButton_2_clicked()));
    connect(ui->Btn_Stop, SIGNAL(clicked(bool)), this, SLOT(Btn_Stop()));

    Init();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::pbtnClicked()
{

    m_timerId=startTimer(1000);
}


void MainWindow::TempInferfaceInit()
{
    qint8 i;

    axisX = new QValueAxis;//新建坐标轴
    axisY = new QValueAxis;
    axisY->setRange(0, yrange);//新建坐标区间
    axisX->setRange(0, xrange);

    axisY->setTickCount(ycount + 1);//设置坐标区间格数
    axisX->setTickCount(xcount + 1);

    axisY->setLabelFormat("%.2f");//设置坐标轴下标的数字类型
    axisX->setLabelFormat("%d");

    axisX->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));//设置字体
    axisY->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));

    axisX->setGridLineVisible(true);//已经隐藏网格线
    axisY->setGridLineVisible(true);

    for(i = 0;i < 4;i++)//添加8条曲线
    {
        SeriesInit(i);
    }
    m_chart->legend()->hide();//图例隐藏
    m_chart->setTitle("Audio Modality");//10.18
    m_chart->layout()->setContentsMargins(0, 0, 0, 0);
    m_chart->setMargins(QMargins(0, 0, 0, 0));
    m_chart->setBackgroundRoundness(0);

    //将series添加到图表中
    chartView = new ChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //添加到界面中
    ui->verticalLayout->addWidget(chartView);

}

void MainWindow::TempInferfaceInit_2()
{
    qint8 i;

    axisX_2 = new QValueAxis;
    axisY_2 = new QValueAxis;

    axisY_2->setRange(0, yrange);
    axisX_2->setRange(0, xrange);

    axisY_2->setTickCount(ycount + 1);
    axisX_2->setTickCount(xcount + 1);

    axisY_2->setLabelFormat("%.2f");
    axisX_2->setLabelFormat("%d");

    axisX_2->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    axisY_2->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));

    axisX_2->setGridLineVisible(true);
    axisY_2->setGridLineVisible(true);

    for(i = 0;i < 4;i++)
    {
        SeriesInit_2(i);
    }
    m_chart_2->legend()->hide();
    m_chart_2->setTitle("Video Modality");
    m_chart_2->layout()->setContentsMargins(0, 0, 0, 0);
    m_chart_2->setMargins(QMargins(0, 0, 0, 0));
    m_chart_2->setBackgroundRoundness(0);

    chartView_2 = new ChartView(m_chart_2);
    chartView_2->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout_2->addWidget(chartView_2);
}

void MainWindow::TempInferfaceInit_3()
{
    qint8 i;

    axisX_3 = new QValueAxis;
    axisY_3 = new QValueAxis;

    axisY_3->setRange(0, yrange);
    axisX_3->setRange(0, xrange);

    axisY_3->setTickCount(ycount + 1);
    axisX_3->setTickCount(xcount + 1);

    axisY_3->setLabelFormat("%.2f");
    axisX_3->setLabelFormat("%d");

    axisX_3->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    axisY_3->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));

    axisX_3->setGridLineVisible(true);
    axisY_3->setGridLineVisible(true);

    for(i = 0;i < 4;i++)
    {
        SeriesInit_3(i);
    }
    m_chart_3->legend()->hide();
    m_chart_3->setTitle("Multimodal Modality");
    m_chart_3->layout()->setContentsMargins(0, 0, 0, 0);
    m_chart_3->setMargins(QMargins(0, 0, 0, 0));
    m_chart_3->setBackgroundRoundness(0);

    chartView_3 = new ChartView(m_chart_3);
    chartView_3->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout_3->addWidget(chartView_3);
}

void MainWindow::SeriesInit(qint8 ch)
{
    //新建一条折线
    m_series[ch] = new QLineSeries;

    //添加到chart
    m_chart->addSeries(m_series[ch]);

    switch(ch)
    {
        //设置颜色和线的大小
        case 0:m_series[ch]->setPen(QPen(Qt::black,2,Qt::SolidLine));break;
        case 1:m_series[ch]->setPen(QPen(Qt::green,2,Qt::SolidLine));break;
        case 2:m_series[ch]->setPen(QPen(Qt::blue,2,Qt::SolidLine));break;
        case 3:m_series[ch]->setPen(QPen(Qt::red,2,Qt::SolidLine));break;
    }

    //将其添加到坐标轴
    m_chart->setAxisX(axisX,m_series[ch]);
    m_chart->setAxisY(axisY,m_series[ch]);
    //关联显示函数
    connect(m_series[ch],  SIGNAL(hovered(QPointF, bool)), this, SLOT(showPointData(QPointF,bool)));
}

void MainWindow::SeriesInit_2(qint8 ch)
{
    //新建一条折线
    m_series_2[ch] = new QLineSeries;

    //添加到chart
    m_chart_2->addSeries(m_series_2[ch]);
    switch(ch)
    {
        //设置颜色和线的大小
        case 0:m_series_2[ch]->setPen(QPen(Qt::black,2,Qt::SolidLine));break;
        case 1:m_series_2[ch]->setPen(QPen(Qt::green,2,Qt::SolidLine));break;
        case 2:m_series_2[ch]->setPen(QPen(Qt::blue,2,Qt::SolidLine));break;
        case 3:m_series_2[ch]->setPen(QPen(Qt::red,2,Qt::SolidLine));break;
    }
    //将其添加到坐标轴
    m_chart_2->setAxisX(axisX_2,m_series_2[ch]);
    m_chart_2->setAxisY(axisY_2,m_series_2[ch]);

}

void MainWindow::SeriesInit_3(qint8 ch)
{
    //新建一条折线
    m_series_3[ch] = new QLineSeries;
    //添加到chart
    m_chart_3->addSeries(m_series_3[ch]);
    switch(ch)
    {
        //设置颜色和线的大小
        case 0:m_series_3[ch]->setPen(QPen(Qt::black,2,Qt::SolidLine));break;
        case 1:m_series_3[ch]->setPen(QPen(Qt::green,2,Qt::SolidLine));break;
        case 2:m_series_3[ch]->setPen(QPen(Qt::blue,2,Qt::SolidLine));break;
        case 3:m_series_3[ch]->setPen(QPen(Qt::red,2,Qt::SolidLine));break;
    }
    //将其添加到坐标轴
    m_chart_3->setAxisX(axisX_3,m_series_3[ch]);
    m_chart_3->setAxisY(axisY_3,m_series_3[ch]);

}

//控制按键
void MainWindow::Btn_Stop()
{
    if (QObject::sender() == ui->Btn_Stop)
    {
        if (!isStopping)
        {
            TempTime->start();
            TempTime_2->start();
            TempTime_3->start();

            //play();
            mediaPlayer->play();
            m_timerId=startTimer(1000);
            ui->Btn_Stop->setText("Suspend");

        }
        else
        {
            TempTime->stop();
            TempTime_2->stop();
            TempTime_3->stop();
            mediaPlayer->pause();

            //play();

            this->killTimer(this->m_timerId);
            ui->Btn_Stop->setText("Start");
        }
        isStopping = !isStopping;
    }

}


//显示函数
void MainWindow::showPointData(QPointF position, bool isHovering)
{

    if (tip == 0)
        tip = new Callout(m_chart);

    if (isHovering)
    {

        tip->setText(QString("emtion: %1 \nlevel: %2 ").arg(currentChangel+1).arg(QString::number(position.y(),'f',2)));
        tip->setAnchor(position);
        tip->setZValue(11);
        tip->updateGeometry();
        tip->show();
    } else
    {
        tip->hide();
    }
}

//视频离散接口部分
// void MainWindow::receiveslot(float videoDiscrete)
void MainWindow::receiveslot(vector<float> audioScoreVector)
{
#if 1

    int i,j;
    QVector<QPointF> oldData[4];
    QVector<QPointF> data[4];
    qint64 size[4];
    current_audioscore = audioScoreVector[0];

    if(isVisible())

    {
        if(TempTime->isActive())
        {

            for(j = 0;j < 4;j++)
            {


                oldData[j] = m_series[j]->pointsVector();
                //mediaPlayer->play();
                if (oldData[j].size() < 1000)//控制曲线突然变快
                {
                    data[j] = oldData[j];
                }
                else
                {
                    // 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
                    //  由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改

                    for (i = 1; i < oldData[j].size(); ++i)
                    {
                        data[j].append(QPointF(i - 1, oldData[j].at(i).y()));
                    }

                }
                size[j] = data[j].size();
                //qDebug()<<"size of data[j] is:"<<data[j].size();//9.3
            }

            // 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
             //但为了后面方便插入多个数据，先这样写
            for(i = 0; i < 1; ++i)
            {
                for(j = 0;j < 4;j++)
                {

                   //qDebug()<<"!!!!!!size of now_audio[j] is:"<<videoDiscrete[j];//9.3
                   data[j].append(QPointF(i + size[j], audioScoreVector[j]));

                   if(i + size[j]>(xcount-1))
                   {
                       axisX->setRange(i + size[j] - xcount, i + size[j]);// 第一个
                   }
                }
            }
            for(j = 0;j < 4;j++)
            {
                m_series[j]->replace(data[j]);
            }
            /*
            if(current_audioscore <= none)
            {
                m_series[0]->setPen(QPen(Qt::green,2,Qt::SolidLine));
                m_series[1]->setPen(QPen(Qt::transparent,2,Qt::SolidLine));
                m_series[2]->setPen(QPen(Qt::transparent,2,Qt::SolidLine));
                m_series[3]->setPen(QPen(Qt::transparent,2,Qt::SolidLine));
            }
            if((current_audioscore <= mild) & (current_audioscore > none))
            {
                m_series[0]->setPen(QPen(Qt::transparent,2,Qt::SolidLine));
                m_series[1]->setPen(QPen(Qt::blue,2,Qt::SolidLine));
                m_series[2]->setPen(QPen(Qt::transparent,2,Qt::SolidLine));
                m_series[3]->setPen(QPen(Qt::transparent,2,Qt::SolidLine));
            }
            if(current_audioscore <= moderate & current_audioscore > mild)
                {m_series[0]->setPen(QPen(Qt::red,2,Qt::SolidLine));}
            if(current_audioscore <= severe & current_audioscore > moderate)
                {m_series[0]->setPen(QPen(Qt::black,2,Qt::SolidLine));}

            //m_series[1]->setPen(QPen(Qt::transparent,2,Qt::SolidLine));
            //m_series[2]->setPen(QPen(Qt::transparent,2,Qt::SolidLine));
            //m_series[3]->setPen(QPen(Qt::transparent,2,Qt::SolidLine));
            */
        }//TempTime
    }
    #endif

}

//音频离散接口部分
// void MainWindow::receiveslot_2(float audioDiscrete)
void MainWindow::receiveslot_2(vector<float> videoScoreVector)
{
#if 1
/******音频接口********/

    int i,j;
    QVector<QPointF> oldData[4];
    QVector<QPointF> data[4];
    qint64 size[4];
    current_videoscore = videoScoreVector[0];
    if(isVisible())
    {
        if(TempTime->isActive())
        {
            for(j = 0;j < 4;j++)
            {

               oldData[j] = m_series_2[j]->pointsVector();
               //qDebug()<<"size of oldData[j] is:"<<oldData[j].size();//9.3
                if (oldData[j].size() < 1000)//控制曲线突然变快
                {
                    //qDebug()<<"if oldData[j].size() < 1000---------------"<<endl;
                    data[j] = oldData[j];
                }
                else
                {
                    // 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
                    //  由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
                    //qDebug()<<" else---------------"<<endl;

                    for (i = 1; i < oldData[j].size(); ++i) {
                        data[j].append(QPointF(i - 1, oldData[j].at(i).y()));
                    }

                }
                size[j] = data[j].size();
                //qDebug()<<"size of data[j] is:"<<data[j].size();//9.3
            }

            // 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
             //但为了后面方便插入多个数据，先这样写


            for(i = 0; i < 1; ++i)
            {
                for(j = 0;j < 4;j++)
                {
                   //qDebug()<<"!!!!!!size of now_audio[j] is:"<<audioDiscrete[j];//9.3
                   data[j].append(QPointF(i + size[j],videoScoreVector[j]));

                   if(i + size[j]>(xcount-1))
                   {
                       axisX_2->setRange(i + size[j] - xcount, i + size[j]);// 第二个
                   }
                }
            }
            for(j = 0;j < 4;j++)
            {
                m_series_2[j]->replace(data[j]);
            }
        }//TempTime
    }
   #endif
}

//多模态离散接口部分
// void MainWindow::receiveslot_3(float multimodalDiscrete)
void MainWindow::receiveslot_3(vector<float> multimodalScoreVector)
{
#if 1
/******音频接口********/

    int i,j;
    QVector<QPointF> oldData[4];
    QVector<QPointF> data[4];
    qint64 size[4];
    current_multimodalscore = multimodalScoreVector[0];
    if(isVisible())
    {
        if(TempTime->isActive())
        {

            for(j = 0;j < 4;j++)
            {
               oldData[j] = m_series_3[j]->pointsVector();
               //qDebug()<<"size of oldData[j] is:"<<oldData[j].size();//9.3
                if (oldData[j].size() < 1000)//控制曲线突然变快
                {
                    //qDebug()<<"if oldData[j].size() < 1000---------------"<<endl;
                    data[j] = oldData[j];
                }
                else
                {
                    // 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
                    //  由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
                    //qDebug()<<" else---------------"<<endl;

                    for (i = 1; i < oldData[j].size(); ++i) {
                        data[j].append(QPointF(i - 1, oldData[j].at(i).y()));
                    }

                }
                size[j] = data[j].size();
                //qDebug()<<"size of data[j] is:"<<data[j].size();//9.3
            }

            // 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
             //但为了后面方便插入多个数据，先这样写


            for(i = 0; i < 1; ++i)
            {
                for(j = 0;j < 4;j++)
                {
                    int tt = i + size[j] - xcount;
                   //qDebug()<<"!!!!!!size of now_audio[j] is:"<<multimodalDiscrete;//9.3
                   data[j].append(QPointF(i + size[j],multimodalScoreVector[j]));
                   if(i + size[j]>(xcount-1))
                   {
                       axisX_3->setRange(i + size[j] - xcount, i + size[j]);// 第二个
                   }
                }
            }
            for(j = 0;j < 4;j++)
            {
                m_series_3[j]->replace(data[j]);
            }
        }

    }
   #endif
}



// 视频部分
void MainWindow::Init()
{
    //设置主界面背景
    this->setWindowTitle(QString::fromLocal8Bit("DepressionDetection"));

    //创建mediaPlayer
    //ui->widget->setAspectRatioMode(Qt::IgnoreAspectRatio);//-----------------------------------------------------------------
    mediaPlayer = new QMediaPlayer(this);


    //设置mediaPlayer的QVideoWidget播放窗口
    mediaPlayer->setVideoOutput(ui->widget);

    //设置打开文件按钮

    ui->toolButton->setToolTip(QString::fromLocal8Bit("打开文件"));
    ui->toolButton->setAutoRaise(true);//设置自动获取状态
    ui->toolButton->setIconSize(QSize(75,75));

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(ui->toolButton);

    connect(ui->toolButton, SIGNAL(clicked(bool)), this, SLOT(on_toolButton_2_clicked()));

}

void MainWindow::play()
{
    switch (mediaPlayer->state())
    {
        case QMediaPlayer::PlayingState:
                mediaPlayer->pause();
                break;
        default:
        //数据接口
        dealThread *dealthread = new dealThread();
        dealthread->start();
        dealthread->myfilename = filenames;

        //qRegisterMetaType<float>("float");//9.24
        //qRegisterMetaType<float>("float");//9.24
        //qRegisterMetaType<float>("float");//9.24
        //connect(dealthread, SIGNAL(sendData(float)), SLOT(receiveslot(float)), Qt::QueuedConnection);
        //connect(dealthread, SIGNAL(sendData2(float)), SLOT(receiveslot_2(float)), Qt::QueuedConnection);
        //connect(dealthread, SIGNAL(sendData3(float)), SLOT(receiveslot_3(float)), Qt::QueuedConnection);

        qRegisterMetaType<vector<float>>("vector<float>");
        qRegisterMetaType<vector<float>>("vector<float>");
        qRegisterMetaType<vector<float>>("vector<float>");
        qRegisterMetaType<vector<float>>("vector<float>");
        connect(dealthread, SIGNAL(sendData(vector<float>)), SLOT(receiveslot(vector<float>)), Qt::QueuedConnection);
        connect(dealthread, SIGNAL(sendData2(vector<float>)), SLOT(receiveslot_2(vector<float>)), Qt::QueuedConnection);
        connect(dealthread, SIGNAL(sendData3(vector<float>)), SLOT(receiveslot_3(vector<float>)), Qt::QueuedConnection);

        connect(dealthread, &dealThread::finished, dealthread, &QObject::deleteLater);
        mediaPlayer->play();
        break;
    }

}

void MainWindow::on_toolButton_2_clicked()
{
    //qDebug()<<QString(avcodec_configuration());
    //qDebug()<<"version:"<<QString::number(avcodec_version());;
    QString filename = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开视频"),".",tr("*.mp4 *.avi"));
    //qDebug()<<filename<<endl;
    filenames = QUrl::fromLocalFile(filename).toLocalFile().toStdString();

    //设置播放内容
    mediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    //mediaPlayer->play();
    play();

}

