/************************************************************************/
/* VisionFaceFeature.h
/* Created by cdd on 2015-11-18
/* Copyright (c) 2015 Vision.EE.Thu, All rights reserved.
/* Modify:
/*   2016-11-15 change recognition model
/************************************************************************/

#ifndef VISIONFACEFEATURE_H
#define VISIONFACEFEATURE_H

#include <vector>
#include "opencv2/opencv.hpp"

#if defined (_MSC_VER) || defined (_WIN32) || defined (_WIN64)
#ifdef THUVISIONFACEFEATURESIMPLE_EXPORTS
#define  VISION_API __declspec(dllexport)
#else
#define  VISION_API __declspec(dllimport)
#endif // VISION_API
#else // defined (windows)
#define VISION_API
#endif

namespace vision{
	class VISION_API VisionFaceFeature
	{
	public:
		virtual ~VisionFaceFeature(){}
		/*! Model init
		_device_id: gpu id
		return:
		true: if init succeed
		false: if init failed
		*/
		virtual bool Init(std::string _param_path = "models/model.json", int _device_id = 0) = 0;

		/*! Return features of an aligned face
		img: face image
		return:
		feature vector
		*/
		virtual std::vector<float> GetFeature(const cv::Mat& img) = 0;

		/*! Return a similarity score[0-1] of a give face pair(features)
		*/
		virtual float GetScore(const std::vector<float>& fea1, const std::vector<float>& fea2) = 0;
	};

	VISION_API VisionFaceFeature* instantiateVisionFaceFeature();
	VISION_API void destroyVisionFaceFeature(VisionFaceFeature* ptr);
}
#endif
