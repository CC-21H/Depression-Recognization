#pragma once
#include <map>
#include <string>
#include <vector>

using namespace std;


#ifdef __cplusplus
extern "C"
{
#endif

	_declspec(dllexport) void model_inference_feature(string model_path, vector<vector<float>> input_feature, string layer_name, int height, int width, int flag, vector<float> result);
	_declspec(dllexport) float model_inference_score(string model_path, vector<vector<float>> input_feature, string layer_name, int height, int width, int flag);

#ifdef __cplusplus
}
#endif
