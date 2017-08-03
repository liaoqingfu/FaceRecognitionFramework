/************************************************************************/
/* VisionExtractFeature.h
/* Created by cdd on 2015-11-18
/* Copyright (c) 2015 Vision.EE.Thu, All rights reserved.
/* Modify:
/*   2016-11-15 change recognition model
/************************************************************************/

#ifndef VISIONEXTRACTFEATURE_H
#define VISIONEXTRACTFEATURE_H

#include <vector>

#if defined (_MSC_VER) || defined (_WIN32) || defined (_WIN64)
#ifdef THUVISIONEXTRACTFEATURE_EXPORTS
#define  VISION_API __declspec(dllexport)
#else
#define  VISION_API __declspec(dllimport)
#endif // VISION_API
#else // defined (windows)
#define VISION_API
#endif

namespace vision{
	class VISION_API VisionExtractFeature
	{
	public:
		virtual ~VisionExtractFeature(){}
		/*! Model init
		i_net_par_path: model path
		_device_id: gpu id
		return:
		true: if init succeed
		false: if init failed
		*/
		virtual bool Init(std::string i_net_par_path, int i_device_id = 0) = 0;

		/*! Get feature
		###############################################################################
		# Data propare example:
		# C: channel; H:height; W:width
		# std::vector<float> data(C * H * W);
		# const float channelMean[3] = { 104, 117, 123 };
		# float scale = 0.0078125;
		# cv::Mat resizedIm = img.clone();
		# float *input = input_blob_ptr->mutable_cpu_data();
		#
		# if (img.rows != H || img.cols != W)
		# {
		#	cv::resize(resizedIm, resizedIm, cv::Size(W, H));
		# }
		#
		# for (int c = 0; c < C; ++c) {
		# 	for (int h = 0; h < H; ++h) {
		# 		for (int w = 0; w < W; ++w) {
		# 			float pixel = static_cast<float>(resizedIm.at<cv::Vec3b>(h, w)[c]);
		# 			data[(c * H + h) * W + w] = (pixel - channelMean[c]) * scale;
		# 		}
		# 	}
		# }
		################################################################################
		return:
		feature vector
		*/
		virtual std::vector<float> GetFeature(const std::vector<float> &data, int i_C, int i_H, int i_W, bool norm_flag = true) = 0;
	};

	VISION_API VisionExtractFeature* instantiateVisionExtractFeature();
	VISION_API void destroyVisionExtractFeature(VisionExtractFeature* ptr);
}
#endif // VISIONEXTRACTFEATURE_H
