///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017, Hann, Tsinghua University
// A branch of OpenFace Framework which uses KCF to stabilize face detection,
//     alignment, and feature extration.
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __VISION_FACE_TRACKER_PARAMS_h_
#define __VISION_FACE_TRACKER_PARAMS_h_

#include <vector>
#include <string>

#ifndef VISION_FACE_TRACKER_API
#ifdef _WIN32
#ifdef VISION_FACE_TRACKER_EXPORT
#define VISION_FACE_TRACKER_API __declspec(dllexport)
#else
#define VISION_FACE_TRACKER_API __declspec(dllimport)
#endif
#else
#define VISION_FACE_TRACKER_API
#endif
#endif

namespace cf_tracking
{
	struct KcfParameters;
	class KcfTracker;
}

namespace vision
{

	struct VISION_FACE_TRACKER_API VisionFaceTrackerParams
	{
		bool verbose;

		// How often should face detection be used to attempt initialisation, every n frames
		int init_video_every;
		int assign_fakeid_after;
		int validation_detect_every;
		float validation_score_threshold;
		int model_abandoned_after;
		float detection_nonoverlap_iou;
#ifndef SINGLE_MODEL_ONLY
		float rediscover_feature_threshold;
		int dulplicate_check_every;
		float dulplicate_threshold;
#endif
		int calc_aligned_face_every;
		int max_aligned_face_number;
		size_t max_face_model_number;

		float face_detect_scale_factor;
		int face_detect_step_size;
		int face_detect_min_face;
		int face_detect_max_face;


		// Determining which face detector to use for (re)initialisation, HAAR is quicker but provides more false positives and is not goot for in-the-wild conditions
		// Also HAAR detector can detect smaller faces while HOG SVM is only capable of detecting faces at least 70px across
		enum FaceDetectorType { HOG_SVM_DETECTOR = 0, VISION_FACE_DETECTOR = 1};
#ifdef USE_DLIB_ALIGNMENT
		std::string dlib_alignment_model_location;
#endif
		FaceDetectorType curr_face_detector;

		cf_tracking::KcfParameters *kcf_tracker_params;

		VisionFaceTrackerParams();
		VisionFaceTrackerParams(std::string config_file_path);
		VisionFaceTrackerParams(const VisionFaceTrackerParams& other);
#ifdef USE_CPP11_STD
		VisionFaceTrackerParams(const VisionFaceTrackerParams&& other);
#endif
		~VisionFaceTrackerParams();

	private:
		void init();
	};

}

#endif // __LANDMARK_DETECTOR_PARAM_H
