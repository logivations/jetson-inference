//
// Created by sanjeev on 22.05.17.
//

#include "barcodeDecoder.h"
#include "L_Types.h"
#include <stdio.h>

#include <cv.h>
#include <highgui.h>
#include<algorithm>

std::vector<std::string> decodeBarcode(cv::Mat imageMat, float *roi) {
//    int x = roi[0], y = roi[1], w = roi[2] - roi[0], h = roi[3] - roi[1];
    int x = std::max(roi[0], 0.0f), y = std::max(roi[1], 0.0f), w = std::max(roi[2] - roi[0], 0.0f), h = std::max(
            roi[3] - roi[1], 0.0f);

    printf("Detect barcode in region: h %d, w %d\n", h, w);

    cv::Rect roiRectangle(x, y, w, h);
    cv::Mat subImg = imageMat(roiRectangle).clone();

    PL_Decoder pDecoder = Connect_L_Decoder(h, w);
    TRow *subimg_idx = (TRow *) malloc(h * sizeof(TRow)); // pointers to ScanLines
    for (int row = 0; row < h; row++) {
        subimg_idx[row] = &subImg.data[w * row];
    }

//    cv::imshow("showImg", subImg);
//    cvWaitKey(0);

    TL_Info *pl_info;
    // create the options
    TL_OptMode opt;
    opt.maxLcount = 10;
    opt.typeCode = TC_ANY; // All codes
    opt.paramQ = 1;      // calc paramq;
    opt.checkSum_I25 = 0;   // off checksum_I25;
    opt.checkSum_C39 = 0;   // off checksum_C39;
    opt.checkSum_CB = 0;    // off checksum_CB;
    opt.FullASCII_C39 = 0;  // FullASCII_C39;
    opt.quietZone = -1;     // quietzone;
    opt.smartmode = 0; //1; // smartmode
    opt.EC_Factor = 0;      // EC_Factor
    opt.pharmacodedir = 0;  // pharmacodedir
    opt.scandir = 2;      // scandir = vertical+horizontal;
    opt.scanstep = 8;      // scanstep;
    opt.colbeg = -1;     // colbeg
    opt.colend = -1;     // colend
    opt.rowbeg = -1;     // rowbeg
    opt.rowend = -1;     // rowend
    opt.TADF_num = 99;     // TADF_num
    opt.color = L_DEFAULT; // color any

    PL_Options pDecWithOpt = Create_L_Options(pDecoder, opt);

    Decode_L_Bits(pDecWithOpt, h, w, subimg_idx);

    TL_ImageInfo *pl_imageinfo = GetL_ImageInfo(pDecWithOpt);
    printf("Total decoded barcodes:%d\n", pl_imageinfo->LCount);

    std::vector<std::string> decodedBarcodes;
    for (int i = 0; i < pl_imageinfo->LCount; i++) {
        pl_info = GetL_Info(pDecWithOpt, i);
        printf("Decoded barcode value: %s\n", pl_info->pch);
        std::string decodedbarcode(pl_info->pch);
        decodedBarcodes.push_back(decodedbarcode);
    }
    free(subimg_idx);
    return decodedBarcodes;
}