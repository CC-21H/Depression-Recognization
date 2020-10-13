#ifndef DEALTHREAD_H
#define DEALTHREAD_H

#include <QThread>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <QVector>
#include <QMap>
#include <QMetaType>
#include <QTimer>
#include <QTimerEvent>
#include <include\opencv2\dnn.hpp>
#include <include\opencv2\highgui\highgui.hpp>
#include <include\opencv2\imgproc\imgproc.hpp>
#include <include\opencv2\core\utils\trace.hpp>
#include <include\opencv2/opencv.hpp>//

using namespace std;
using namespace cv;

class dealThread : public QThread
{
    Q_OBJECT



public:
    dealThread();
    void run();
    int getAudioInfo(char *file_name);
    string myfilename;
    string myfilename1;
    bool JudgeFileExists(string filePath);
    string int2str(int num);
    vector<vector<string>> selectFramesFromVideo(cv::VideoCapture& capture, string saveRoot);
    string GainBasename(string filePath);
    int GetVideoDuration(string aviPath);
    string readSubAvi(string aviPath, int start_time, int duration, string saveRoot);
    string readWavFromVideo(string aviPath, string wavRoot);
    vector<float> convertMat2Vector(const Mat &mat);
    vector<vector<float>> get_vedio_data(vector<float> v, int h, int w);
    string readOpensmileFeats(string wavPath, string saveRoot);
    Mat SelectSingleFrmae(string ClipPath);
    vector<vector<float>> readeGemapsLieFeats(string featurePath);
    int Score2State(float s);
    string getDirPath(string s);



signals:
    //void sendData(float audioScore);
    //void sendData2(float videoScore);
    //void sendData3(float multimodalScore);

    void sendData(vector<float> audioScoreVector);
    void sendData2(vector<float> videoScoreVector);
    void sendData3(vector<float> multimodalScoreVector);

};

#endif // DEALTHREAD_H
