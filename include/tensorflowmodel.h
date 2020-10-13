#pragma once
#ifndef _TENSORFLOWMODEL_H
#define _TENSORFLOWMODEL_H

#include "..\include\main.h"

TF_Buffer* read_file(string file);

void free_buffer(void* data, size_t length);
int load_frozen_model(string pb_file, TF_Graph* graph, TF_Status* status);
void print_operations(TF_Graph* graph);
void int_array_to_str(int64_t* arr, int len, char* buff);

void load_audio_data(float* input_data, vector<vector<float>> audioDepressionFeature);
void load_video_data(float* input_data, vector<vector<float>> video_features);

int64_t desc_tensor(TF_Tensor* t);

//void model_inference_feature(const char* model_path, vector<vector<float>> input_feature, const char* layer_name, int height, int width, int flag, float* result);
//void model_inference_score(const char* model_path, vector<vector<float>> input_feature, const char* layer_name, int height, int width, int flag, float* score);
Mat SelectSingleFrmae(string ClipPath);
vector<float> convertMat2Vector(const Mat &mat);
vector<vector<float>> get_vedio_data(vector<float> v, int h, int w);
//flag:0表示进行语音预测，flag：1表示进行视频预测

#endif
