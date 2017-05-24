//
// Created by sanjeev on 24.05.17.
//

#ifndef JETSON_INFERENCE_IMAGEUTILS_H
#define JETSON_INFERENCE_IMAGEUTILS_H

#include <cv.h>
#include <vector_types.h>

cv::Mat rgbaToGray(float4 *rgbaImg, int h, int w);

void drawBBox(cv::Mat &img, float *bbox);

void renderBarcodeValue(cv::Mat &img, float *bbox, const char *barcodeValue);

#endif //JETSON_INFERENCE_IMAGEUTILS_H
