#pragma once
#ifndef _SUBFUNCTION_H
#define _SUBFUNCTION_H

#include "..\include\main.h"

string int2str(int num);
void getFiles(string path, vector<string>& files);
string GainBasename(string filePath);
void CreateDir(string szDirName);
bool RemoveDir(string szDirName);
bool JudgeFileExists(string filePath);
string readWavFromVideo(string aviPath, string wavRoot);
string readSubAvi(string aviPath, int start_time, int duration, string saveRoot);
string readSubWav(string aviPath, int start_time, int duration, string saveRoot);
string readOpensmileFeats(string wavPath, string saveRoot);
int GetVideoDuration(string aviPath);
vector<vector<float>> readeGemapsLieFeats(string featurePath);

string writeCSV(string aviPath, string savePath, Mat m);
vector<vector<float>> readCSV(string csvPath);
void DeleteRoot(string Root);
void OuputFeature(float* Feature);
void NormalizationFeature(vector<float> feature, vector<float> norFeature);
int DepressionState(float s);
int Score2State(float s);


#endif
