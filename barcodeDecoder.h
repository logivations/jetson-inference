//
// Created by sanjeev on 22.05.17.
//

#ifndef JETSON_INFERENCE_BARCODEDECODER_H
#define JETSON_INFERENCE_BARCODEDECODER_H

#include<vector>
#include<string>
#include<cv.h>

std::vector<std::string> decodeBarcode(cv::Mat imageMat, float *roi);

#endif //JETSON_INFERENCE_BARCODEDECODER_H
