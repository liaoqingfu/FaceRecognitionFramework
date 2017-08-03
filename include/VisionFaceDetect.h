/************************************************************************/
/* VisionFaceDetect.h
/* Created by cdd on 2016-11-15
/* Copyright (c) 2016 Vision.EE.Thu, All rights reserved.
/* Modify:
/************************************************************************/

#ifndef VISIONFACEDETECT_H
#define VISIONFACEDETECT_H

#if defined (_MSC_VER) || defined (_WIN32) || defined (_WIN64)
#ifdef VISIONFACEDETECT_EXPORTS
#define  VISION_API __declspec(dllexport)
#else
#define  VISION_API __declspec(dllimport)
#endif // VISION_API
#else // defined (windows)
#define VISION_API
#endif

#include <iostream>
#include "opencv2/opencv.hpp"

namespace vision{
	enum DetectionSpeed
	{
		SLOW,
		NORMAL,
		FAST
	};

	class VISION_API VisionFaceDetect
	{
	public:
		virtual ~VisionFaceDetect(){}
		virtual bool Init(std::string model_path = "") = 0;
		virtual void SetPar(float _scale_factor, int _step_size, int _min_face_size, int _max_face_size) = 0;
		virtual void SetScaleFactor(float _scale_factor) = 0;
		virtual void SetStepSize(int _step_size) = 0;
		virtual void SetMinFaceSize(int _min_face_size) = 0;
		virtual void SetMaxFaceSize(int _max_face_size) = 0;
		virtual void SetPar(DetectionSpeed type = vision::NORMAL) = 0;
		virtual std::vector<cv::Rect> GetMaximumFace(const cv::Mat& img) = 0;
		virtual std::vector<cv::Rect> GetFaces(const cv::Mat& img) = 0;
		virtual std::vector<std::pair<cv::Rect, float> > GetFacesWithWeights(const cv::Mat& img) = 0;
		virtual std::vector<std::pair<cv::Rect, float> > GetMaximumFaceWithWeights(const cv::Mat& img) = 0;
		virtual void DrawFaceRect(cv::Mat& img, cv::Rect face_rect) = 0;
	};

	VISION_API VisionFaceDetect* instantiateVisionFaceDetect();
	VISION_API void destroyVisionFaceDetect(VisionFaceDetect* ptr);
}
#endif // VISIONFACEDETECT_H