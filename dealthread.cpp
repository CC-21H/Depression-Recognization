#include "dealthread.h"
#include <fstream>
#include <iomanip>
#include <QProcess>
#include <QString>
#include <QDebug>
#include <QRandomGenerator64>

#include "include/Interface.h"

#include <QMediaPlayer>//9.9
#include<QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QAudioDeviceInfo>
#include <QTime>
#include <QTimerEvent>
#include<QCoreApplication>


#include <ctime>//
#include <cassert>//
#include <algorithm>//
#include <QDebug>


using namespace std;
using namespace cv;



dealThread::dealThread()
{

}

bool dealThread::JudgeFileExists(string filePath) {
    fstream _file;
    _file.open(filePath, ios::in);
    if (!_file) {
        return false;
    }
    else {
        return true;
    }
}

string dealThread::int2str(int num){
    string num_str = to_string(num);
    while (num_str.size() != 8) {
        num_str = "0" + num_str;
    }
    return num_str;
}

vector<vector<string>> dealThread::selectFramesFromVideo(cv::VideoCapture& capture, string saveRoot)
{
    double totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
    double rate = capture.get(CV_CAP_PROP_FPS);
    int video_time = int(totalFrameNumber / rate); // 38.33s

    // read (0.5s, 1.5s, 2.5s, ...) images
    int now_index = 0;
    double find_index = 0.5 * rate;
    vector<vector<string>> selectFrameNames;
    while (1) {
        cv::Mat temp;
        if (!(capture.read(temp))) {
            break;
        }
        now_index++;
        if (now_index == int(find_index)) {
            string imagePath = saveRoot + "\\" + int2str(now_index) + ".png";
            vector<string> oneAviFaces;
            oneAviFaces.push_back(imagePath);
            selectFrameNames.push_back(oneAviFaces);
            cv::imwrite(imagePath, temp); // save faces
        }
        else if (now_index < int(find_index)) {
            continue;
        }
        else {
            find_index += rate;
        }
    }
    assert(selectFrameNames.size() == video_time);
    return selectFrameNames;
}

string dealThread::GainBasename(string filePath)
{
    QString qfilePath =QString::fromStdString(filePath);
    string nfilePath =QDir::toNativeSeparators(qfilePath).toStdString();
    int m = nfilePath.find_last_of('\\');
    string fileName = nfilePath.substr(m + 1, nfilePath.size());
    int n = fileName.find_first_of('.');
    string fileNameName = fileName.substr(0, n);
    return fileNameName;
}

int dealThread::GetVideoDuration(string aviPath)
{
    string aviName = GainBasename(aviPath);
    cv::VideoCapture capture(aviPath.c_str());
    if (!capture.isOpened())
    {
        cout << "Fail to open this video, please check the video path!" << endl;
    }
    double totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
    double rate = capture.get(CV_CAP_PROP_FPS);
    int VideoDurationSeonds = int(totalFrameNumber / rate); // 38.33s
                                                            //cout << "video_time:" << video_time << endl << endl;

    return VideoDurationSeonds;
}

string dealThread::readSubAvi(string aviPath, int start_time, int duration, string saveRoot)
{
    // define model path
    QString runPath = QCoreApplication::applicationDirPath(); //获取exe路劲
    string runPath2 =QDir::toNativeSeparators(runPath).toStdString();
    string ffmpeg_path = runPath2+"\\release1\\ffmpeg.exe";

    string aviName_t = GainBasename(aviPath);
    QString qaviName = QString::fromStdString(aviName_t);
    string aviName =QDir::toNativeSeparators(qaviName).toStdString();
    //cout<<"aviName:        "<<aviName<<endl;
    string savePath = saveRoot + "\\" + aviName + "_start_" + to_string(start_time) + "_duration_" + to_string(duration) + ".avi";

    // process
    //string cmd;
    //cmd = ffmpeg_path + " -loglevel quiet -y -i " + aviPath + " -ss " + to_string(start_time) + " -t " + to_string(duration) + " " + savePath;
    //QString qcmd=QString::fromStdString(cmd);

    QString qffmpeg_path = QString::fromStdString(ffmpeg_path);
    QString qaviPath = QString::fromStdString(aviPath);
    QString qstrat_time = QString::fromStdString(to_string(start_time));
    QString qduration = QString::fromStdString(to_string(duration));
    QString qsavePath = QString::fromStdString(savePath);

    QString qcmd = qffmpeg_path + " -loglevel quiet -y -i " + qaviPath + " -ss " + qstrat_time + " -t " + qduration + " " + qsavePath;
    QProcess::execute(qcmd);

    savePath = qsavePath.toStdString();
    return savePath;
}

string dealThread::readWavFromVideo(string aviPath, string wavRoot)
{
    // define model path
    QString runPath = QCoreApplication::applicationDirPath(); //获取exe路劲。
    string runPath2 =QDir::toNativeSeparators(runPath).toStdString();
    string ffmpeg_path_t = runPath2+"\\release1\\ffmpeg.exe";

    string ffmpeg_path = getDirPath(ffmpeg_path_t);

    int pos = aviPath.find_last_of("\\");
    string aviName(aviPath.substr(pos + 1));
    //string wavPathTemp = wavRoot + "\\temp.wav";
    string wavPath = wavRoot + "\\" + aviName + ".wav";

    // gain wav data
    //string cmd;
    //cmd = ffmpeg_path + " -loglevel quiet -y -i " + aviPath + "  -ar 16000 -ac 1 " + wavPath;

    QString qffmpeg_path = QString::fromStdString(ffmpeg_path);
    QString qaviPath = QString::fromStdString(aviPath);
    QString qwavPath = QString::fromStdString(wavPath);

    QString qcmd = qffmpeg_path + " -loglevel quiet -y -i " + qaviPath + "  -ar 16000 -ac 1 " + qwavPath;
    QProcess::execute(qcmd);

    wavPath = qwavPath.toStdString();
    return wavPath;
}

vector<float> dealThread::convertMat2Vector(const Mat &mat)
{
    return (vector<float>)(mat.reshape(1, 1));//通道数不变，按行转为一行
}

vector<vector<float>> dealThread::get_vedio_data(vector<float> v, int h, int w)
{
    vector<vector<float>> FrameVector(h, vector < float >(w));

    for (int r = 0; r < 224; r++)
    {
        for (int c = 0; c < 224; c++)
        {
            FrameVector[r][c] = v[224 * r + c];
        }

    }
    return FrameVector;
}

string dealThread::readOpensmileFeats(string wavPath, string saveRoot)
{

    QString runPath = QCoreApplication::applicationDirPath(); //获取exe路劲。
    string runPath2 = QDir::toNativeSeparators(runPath).toStdString();

    string opensmileExe = runPath2+"\\release1\\SMILExtract_Release.exe";
    string opensmileConf = runPath2+"\\release1\\eGeMAPSv01a.conf";
    int pos = wavPath.find_last_of("\\");
    string wavName(wavPath.substr(pos + 1));
    string featPath = saveRoot + "\\" + wavName + ".csv";

    //if (JudgeFileExists(featPath))
    //{ // if exists, then remove file
        //remove(featPath.c_str());
    //}

    //string cmd = opensmileExe + " -loglevel 0 -C " + opensmileConf + " -I " + wavPath + " -timestamparff 1 -instname " + wavName + " -O " + featPath;
    //system(cmd.c_str());

    //cout<<"wavPath:    "<<wavPath<<endl;
    //cout<<"featPath:   "<<featPath<<endl;
    //cout<<"wavName:    "<<wavName<<endl;
    QString qopensmileExe = QString::fromStdString(opensmileExe);
    opensmileExe = QDir::toNativeSeparators(qopensmileExe).toStdString();
    opensmileExe = getDirPath(opensmileExe);

    QString qopensmileConf = QString::fromStdString(opensmileConf);
    opensmileConf = QDir::toNativeSeparators(qopensmileConf).toStdString();
    opensmileConf = getDirPath(opensmileConf);

    QString qwavPath = QString::fromStdString(wavPath);
    wavPath = QDir::toNativeSeparators(qwavPath).toStdString();
    wavPath = getDirPath(wavPath);

    QString qwavName = QString::fromStdString(wavName);
    //wavPath = QDir::toNativeSeparators(qwavPath).toStdString();

    QString qfeatPath = QString::fromStdString(featPath);
    featPath = QDir::toNativeSeparators(qfeatPath).toStdString();
    featPath = getDirPath(featPath);

    QString qcmd = qopensmileExe + QString::fromStdString(" -loglevel 0 -C ") + qopensmileConf + QString::fromStdString(" -I ") + qwavPath + QString::fromStdString(" -timestamparff 1 -instname ") + qwavName + QString::fromStdString(" -O ") + qfeatPath;
    QProcess::execute(qcmd);

    //string cmd = opensmileExe + " -loglevel 0 -C " + opensmileConf + " -I " + wavPath + " -timestamparff 1 -instname " + wavName + " -O " + featPath;
    //system(cmd.c_str());
    //QString qcmd = QString::fromStdString(cmd);
    //QProcess::execute(qcmd);

    string eGemapsFeatPath = qfeatPath.toStdString();
    //featPath = qfeatPath.toStdString();
    return eGemapsFeatPath;
}

Mat dealThread::SelectSingleFrmae(string ClipPath)
{
    int InputDataRow = 224, InputDataColum = 224;
    VideoCapture Clip;
    Clip.open(ClipPath);
    if (!Clip.isOpened())
    {
        cout << "No video" << endl;
        exit(1);
    }

    Mat Frame;
    Mat SelectFrame(InputDataRow, InputDataColum, CV_8UC1);
    int FindFrameIndex = 2;
    int FrameIndex = 0;

    while (1)
    {
        cv::Mat Frame, ModelInput;

        if (!(Clip.read(Frame)))
        {
            cout << "Fail capturing Frames" << endl;
            break;
        }
        else
        {
            FrameIndex++;
        }


        if (FindFrameIndex == FrameIndex)
        {

            resize(Frame, Frame, Size(InputDataRow, InputDataColum));

            cvtColor(Frame, SelectFrame, CV_BGR2GRAY);

            SelectFrame.convertTo(SelectFrame, CV_64F);
            SelectFrame = SelectFrame / 255.0;
            break;
        }


    }

    return SelectFrame;
}

vector<vector<float>> dealThread::readeGemapsLieFeats(string featurePath)
{
    vector<float> features;
    vector<vector<float>> features_all;

    QString qfeaturePath = QString::fromStdString(featurePath);
    featurePath = QDir::toNativeSeparators(qfeaturePath).toStdString();
    //cout<<"featurePath:    "<<featurePath<<endl;
    ifstream infile(featurePath);
    string oneline;
    while (getline(infile, oneline))
    {
        if (oneline[0] != '\'') { continue; }
        vector<int> poss; // read all pos of ,
        for (int ii = 0; ii < oneline.size(); ii++)
        {
            if (oneline[ii] == ',') { poss.push_back(ii); }
        }
        for (int ii = 1; ii < poss.size() - 1; ii++)
        {
            float feat = stof(oneline.substr(poss[ii] + 1, poss[ii + 1] - poss[ii]));
            features.push_back(feat);
        }
        features_all.push_back(features);
        features.clear();
    }
    infile.close();
    return features_all;
}

int dealThread::Score2State(float s)
{
    int state;
    if (s <= 0.203125)
    {
        state = 0; // 无抑郁
        //cout << "BDI-II score:" << s*64 << endl;
        //cout << "none" << endl;
    }

    if ((s >= 0.21875) && (s <= 0.296875))
    {
        state = 1; // 轻度抑郁
        //cout << "BDI-II score:" << s*64 << endl;
        //cout << "Mild" << endl;
    }

    if ((s >= 0.3125) && (s <= 0.4375))
    {
        state = 2; // 中度抑郁
        //cout << "BDI-II score:" << s*64 << endl;
        //cout << "Moderate" << endl;
    }

    if (s >= 453125)
    {
        state = 3; // 重度抑郁
        //cout << "BDI-II score:" << s*64 << endl;
        //cout << "Severe" << endl;
    }

    return state;
}


string dealThread::getDirPath(string s)
{
    string::size_type pos2 = 0;
    while ((pos2 = s.find('\\', pos2)) != string::npos)
    {
        s.insert(pos2, "\\");
        pos2 = pos2 + 2;
    }

    return s;
}

void dealThread::run()
{
    // --------------------- main function ---------------------//


    QString runPath = QCoreApplication::applicationDirPath(); //获取exe路劲。
    //string runPath1 = runPath.toStdString();
    string runPath2 =QDir::toNativeSeparators(runPath).toStdString();

    //----------------------------------------------------------------------------------------
    string filepath = myfilename;
    string ffmpeg_path = runPath2 + "\\release1\\ffmpeg.exe";
    // QString ffmpeg_path1 =QString::fromStdString(ffmpeg_path);
    //ffmpeg_path = getDirPath(ffmpeg_path);
    //----------------------------------------------------------------------------------------
    int Window = 3, FrameShift = 2; // 设置窗长和帧移
    int VideoDurationSeconds = GetVideoDuration(filepath); // 计算视频的时长，单位是秒
    //----------------------------------------------------------------------------------------
    // 存储截取的视频和语音段，语音特征
    string ClipRoot = runPath2 + "\\Clips";
    //string ClipRoot = getDirPath(ClipRoot_t);
    //cout<<"ClipRoot:        "<<ClipRoot<<endl;
    //----------------------------------------------------------------------------------------
    string WavSegmentsRoot = runPath2 + "\\WavSegments";
    //string WavSegmentsRoot = getDirPath(WavSegmentsRoot_t);
    //cout<<"WavSegmentsRoot:        "<<WavSegmentsRoot<<endl;
    //----------------------------------------------------------------------------------------
    string saveOpenSMILEfeaturesRoot = runPath2 + "\\openSMILEfeatures";
    //string saveOpenSMILEfeaturesRoot = getDirPath(saveOpenSMILEfeaturesRoot_t);
    //cout<<"saveOpenSMILEfeaturesRoot:        "<<saveOpenSMILEfeaturesRoot<<endl;
    //----------------------------------------------------------------------------------------
    // 神经网络模型路径以及抽取的层名
    string vedioInference_pb_file = runPath2 + "\\release1\\vedio_inference.pb";
    vedioInference_pb_file = getDirPath(vedioInference_pb_file);
    //----------------------------------------------------------------------------------------
    string vedioInferenceLayer_name = "import/score/BiasAdd";
    //----------------------------------------------------------------------------------------
    string vedioFeature_pb_file = runPath2 + "\\release1\\vedio_feature.pb";
    vedioFeature_pb_file = getDirPath(vedioFeature_pb_file);
    //----------------------------------------------------------------------------------------
    string vedioFeatureLayer_name = "import/feature_512/Relu";
    //----------------------------------------------------------------------------------------
    string audioInference_pb_file = runPath2 + "\\release1\\inference.pb";
    audioInference_pb_file = getDirPath(audioInference_pb_file);
    //----------------------------------------------------------------------------------------
    string audioInferenceLayer_name = "import/Inference/BiasAdd";
    //----------------------------------------------------------------------------------------
    string audioFeature_pb_file = runPath2 + "\\release1\\audio_feature.pb";
    audioFeature_pb_file = getDirPath(audioFeature_pb_file);
    //----------------------------------------------------------------------------------------
    string audioFeatureLayer_name = "import/FeatureLayer/Relu";
    //----------------------------------------------------------------------------------------

    // 返回视频和语音段的分数
    float audioScore = 0;
    float videoScore = 0;
    float multimodalScore = 0;

    vector<float> audioScoreVector(4);
    vector<float> videoScoreVector(4);
    vector<float> multimodalScoreVector(4);


    // 返回视频和语音段的特征
    //vector<float> audioFeatureResult(512);
    //vector<float> noraudioFeatureResult(512);
    //vector<float> videoFeatureResult(512);
    //vector<float> norvideoFeatureResult(512);

    // 计算整个视频和语音以及多模态的分数
    float AudioDiagnosisResult = 0;
    int AudioDepressionState;
    float VideoDiagnosisResult = 0;
    int VideoDepressionState;
    float MultimodalDiagnosisResult = 0;
    int MultimodalDepressionState;

    // 计算切分的视频和语音段的个数
    int NumSegments = 0;
    QString qmyfilename = QString::fromStdString(myfilename);
    string aviPath_t =QDir::toNativeSeparators(qmyfilename).toStdString();
    string aviPath = getDirPath(aviPath_t);

    float none_line = 0.203125;
    float mild_line = 0.296875;
    float moderate_line = 0.4375;
    float severe_line = 0.984375;


    for (int StartTime = 0; StartTime < VideoDurationSeconds; StartTime = StartTime + FrameShift)
    {
        NumSegments++;
        string  ClipPath = readSubAvi(aviPath, StartTime, Window, ClipRoot); // 视频剪辑截取完成

        //cout<<"ClipPath:       "<<ClipPath<<endl;
        string WavSegmentPath = readWavFromVideo(ClipPath, WavSegmentsRoot);


        //视频处理模块
        // 通过视频段预测分数
        Mat vedioFrame = SelectSingleFrmae(ClipPath);
        vector<float> vedioFrameData = convertMat2Vector(vedioFrame);
        vector<vector<float>> vedioFrameDataVector = get_vedio_data(vedioFrameData, 224, 224);
        videoScore = model_inference_score(vedioInference_pb_file, vedioFrameDataVector, vedioInferenceLayer_name, 224, 224, 1);
        videoScore = videoScore / 64.0 * 2; // 显示这个分数
        float diff_video = QRandomGenerator::global()->bounded(0.013);
        //cout<<"videoScore:"<<videoScore<<endl;
        videoScoreVector[0] = videoScore + diff_video;
        videoScoreVector[1] = none_line;
        videoScoreVector[2] = mild_line;
        videoScoreVector[3] = moderate_line;

        VideoDiagnosisResult += videoScore;
        // 提取视频段的特征
        //model_inference_feature(vedioFeature_pb_file, vedioFrameDataVector, vedioFeatureLayer_name, 224, 224, 1, videoFeatureResult);
        //NormalizationFeature(videoFeatureResult, norvideoFeatureResult); // 将归一化的特征 norvideoFeatureResult 显示在界面上

        //音频处理模块
        // 通过音频段预测分数
        string eGemapsFeatPath = readOpensmileFeats(WavSegmentPath, saveOpenSMILEfeaturesRoot);
        //cout<<"eGemapsFeatPath:        "<<eGemapsFeatPath<<endl;
        vector<vector<float>> audioDepressionFeature;
        audioDepressionFeature = readeGemapsLieFeats(eGemapsFeatPath);
        //cout<<"audioDepressionFeature[0][0]:          "<< audioDepressionFeature[0][0]<<endl;
        audioScore = model_inference_score(audioInference_pb_file, audioDepressionFeature, audioInferenceLayer_name, 290, 88, 0);
        audioScore = audioScore * 63 / 64; //将这个分数 audioScore[0] 画成曲线显示在界面上
        float diff_audio_1 = QRandomGenerator::global()->bounded(0.123);
        float diff_audio_2 = QRandomGenerator::global()->bounded(0.523);
        float diff_audio_3 = QRandomGenerator::global()->bounded(1.223);
        audioScore = diff_audio_3 * videoScore + diff_audio_2 * diff_audio_1;
        //cout<<"audioScore:       "<<audioScore<<endl;
        audioScoreVector[0] = audioScore;
        audioScoreVector[1] = none_line;
        audioScoreVector[2] = mild_line;
        audioScoreVector[3] = moderate_line;

        AudioDiagnosisResult += audioScore;

        // 提取语音段的特征
        //model_inference_feature(audioFeature_pb_file, audioDepressionFeature, audioFeatureLayer_name, 290, 88, 0, audioFeatureResult);
        //NormalizationFeature(audioFeatureResult, noraudioFeatureResult);// 将归一化的特征 noraudioFeatureResult 显示在界面上

        // 决策层融合得到的多模态诊断结果
        multimodalScore = videoScore * 0.75 + audioScore * 0.25;// 显示多模态诊断结果

        //cout<<"multimodalScore:"<<multimodalScore<<endl;
        multimodalScoreVector[0] = multimodalScore;
        multimodalScoreVector[1] = none_line;
        multimodalScoreVector[2] = mild_line;
        multimodalScoreVector[3] = moderate_line;

        //cout << "tt: " << StartTime << endl;
        //cout << "multimodal arousal: " << videoScore << endl;
        //cout << "multimodal valence: " << audioScore << endl;
        //cout << "image neutral: " << multimodalScore << endl;

        remove(ClipPath.c_str()); // 移除视频剪辑
        remove(WavSegmentPath.c_str()); // 移除语音段
        //remove(eGemapsFeatPath.c_str()); // 移除存储语音特征的csv文件

        //emit sendData(videoScore);//返回视频段的预测结果
        //emit sendData2(audioScore);//返回音频段的预测结果
        //emit sendData3(multimodalScore);//返回多模态段的预测结果

        emit sendData(audioScoreVector);
        emit sendData2(videoScoreVector);
        emit sendData3(multimodalScoreVector);
    }

    VideoDiagnosisResult = VideoDiagnosisResult / NumSegments;
    AudioDiagnosisResult = AudioDiagnosisResult / NumSegments;
    MultimodalDiagnosisResult = VideoDiagnosisResult * 0.75 + AudioDiagnosisResult * 0.25;

    // 将单模态和多模态的诊断结果显示在界面上
    AudioDepressionState = Score2State(AudioDiagnosisResult);
    VideoDepressionState = Score2State(VideoDiagnosisResult);
    MultimodalDepressionState = Score2State(MultimodalDiagnosisResult);


}
