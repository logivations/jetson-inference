//
// Created by sanjeev on 24.05.17.
//

#include <stdlib.h>
#include "imageUtils.h"

cv::Mat rgbaToGray(float4 *rgbaImg, int h, int w) {
    unsigned char *imageData = (unsigned char *) malloc(h * w);

    for (int i = 0; i < h * w; i++) {
        int gray = (int) ((rgbaImg[i].x * 11 + rgbaImg[i].y * 16 + rgbaImg[i].z * 5) / 32);
        imageData[i] = (unsigned char) gray;
    }
    cv::Mat grayImage(h, w, CV_8UC1, imageData);

    return grayImage;
}

void drawBBox(cv::Mat &img, float *bbox) {
    int x = bbox[0], y = bbox[1], w = bbox[2] - bbox[0], h = bbox[3] - bbox[1];
    cv::Rect rect(x, y, w, h);
    printf("Drawing rectangle x:%d, y:%d, w:%d, h:%d\n", x, y, w, h);
    cv::rectangle(img, rect, cv::Scalar(0, 255, 0), 5);
}

void renderBarcodeValue(cv::Mat &img, float *bbox, const char *barcodeValue) {
    cv::Point startPoint(bbox[0], bbox[1]);
    cv::putText(img, barcodeValue, startPoint, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
}
