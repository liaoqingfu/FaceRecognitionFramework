/************************************************************************/
/* VisionFaceAlignment.h
/* Created by cdd on 2015-11-18
/* Copyright (c) 2015 Vision.EE.Thu, All rights reserved.
/* Modify:
/*   2016-11-15 change recognition model
/************************************************************************/

#ifndef VISIONFACEALIGNMENT_H
#define VISIONFACEALIGNMENT_H

#include <vector>
#include "opencv2/opencv.hpp"

#if defined (_MSC_VER) || defined (_WIN32) || defined (_WIN64)
#ifdef VISIONFACEALIGNMENT_EXPORTS
#define  VISION_API __declspec(dllexport)
#else
#define  VISION_API __declspec(dllimport)
#endif // VISION_API
#else // defined (windows)
#define VISION_API
#endif

namespace vision{
    class VISION_API VisionFaceAlignment
    {
    public:
        virtual ~VisionFaceAlignment(){}
        virtual bool Init(std::string _param_path = "models/face_align.json", int _device_id = 0) = 0;
        virtual std::vector<cv::Point2f> GetKeyPoints(const cv::Mat& img, const cv::Rect& face_rect) = 0;

        // Rect crop_rect(25, 40, 125, 160)
        virtual cv::Mat GetAlignedFace(const cv::Mat& img, const cv::Rect& face_rect) = 0;
        virtual cv::Mat GetAlignedFaceSimple(const cv::Mat& img, const cv::Rect& face_rect) = 0;
        virtual cv::Mat GetAlignedFace(const cv::Mat& img, const std::vector<cv::Point2f>& landmarks) = 0;
    };

    VISION_API VisionFaceAlignment* instantiateVisionFaceAlignment();
    VISION_API void destroyVisionFaceAlignment(VisionFaceAlignment* ptr);
}
#endif
