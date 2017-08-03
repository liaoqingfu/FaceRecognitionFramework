///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017, Hann, Tsinghua University
// A branch of OpenFace Framework which uses KCF to stabilize face detection,
//     alignment, and feature extration.
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __VISION_FACE_TRACKER_h_
#define __VISION_FACE_TRACKER_h_

#include "VisionFaceTrackerParams.h"
#include "VisionFaceTrackingInfo.h"

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

namespace tbb
{
	class mutex;
}

namespace vision
{
class VisionFaceModel;

// A main class containing all the modules required for landmark detection
// Face shape model
// Patch experts
// Optimization techniques
class VISION_FACE_TRACKER_API VisionFaceTracker{

public:
	// A default constructor
	VisionFaceTracker();

	// Constructor from a model file
	VisionFaceTracker(VisionFaceTrackerParams& params);
	
	// Copy constructor (makes a deep copy of the detector)
	VisionFaceTracker(const VisionFaceTracker& other);

	// Assignment operator for lvalues (makes a deep copy of the detector)
	VisionFaceTracker & operator= (const VisionFaceTracker& other);

	// Empty Destructor	as the memory of every object will be managed by the corresponding libraries (no pointers)
	~VisionFaceTracker();

#ifdef USE_CPP11_STD
	// Move constructor
	VisionFaceTracker(const VisionFaceTracker&& other);

	// Assignment operator for rvalues
	VisionFaceTracker & operator= (const VisionFaceTracker&& other);
#endif

	// Reset the model (useful if we want to completelly reinitialise, or we want to track another video)
	void Reset();

	// Reset the model, choosing the face nearest (x,y) where x and y are between 0 and 1.
	void Reset(double x, double y);

	// Detection and Tracking function which should be called in each frame.
	// The output vector<VisionFaceTrackingInfo> is sorted by ascending fakeid
	// Return true if all models have a successful landmark detection.  (meaningless in multiple face case, for it will be false most of time)
	bool Track(const cv::Mat &colorscale_image, const cv::Mat_<uchar> &grayscale_image, std::vector<VisionFaceTrackingInfo> &results_out, const int frame_idx = -1);

	// Get the number of active models in current frame.
	// Effective after DetectLandmarksInVideo() is called.
	size_t getActiveModelNum() const
	{
		return _num_active_models;
	}

	// Get the aligned faces for a certain face model.
	// The output vector<VisionAlignedFace> is sorted by descending timestamp
	// Return the number of aligned faces output.
	int getAlignedFaces(int fake_id, std::vector<VisionAlignedFace> &faces_out);

	static int KEY_POINT_NUM;
#ifdef USE_DLIB_ALIGNMENT
	static int KEY_POINT_COMPLEX_NUM;
#endif

private:
	//===========================================================================
	// Member variables 

	std::vector<VisionFaceModel> _face_models;
	size_t _max_face_model_number;
	int _max_aligned_face_number;
	int _init_video_every;
	int _assign_fakeid_after;
	int _validation_detect_every;
	float _validation_score_threshold;
	int _model_abandoned_after;
	float _detection_nonoverlap_iou;
#ifndef SINGLE_MODEL_ONLY
	float _rediscover_feature_threshold;
	int _dulplicate_check_every;
	float _dulplicate_threshold;
#endif
	int _calc_aligned_face_every;
	VisionFaceTrackerParams::FaceDetectorType _curr_face_detector;
	cf_tracking::KcfParameters *_kcf_params;
	bool _verbose;
	float _face_detect_scale_factor;
	int _face_detect_step_size;
	int _face_detect_min_face;
	int _face_detect_max_face;

	size_t _frame_count;
	size_t _num_active_models;

	tbb::mutex *_fakeid_lock;

#ifdef USE_DLIB_ALIGNMENT
	std::string _dlib_alignment_model_location;
#endif

	//============================================================================
	// Face detection helpers
	//============================================================================
	// Face detection using HOG-SVM classifier
	bool _DetectFacesHOG(size_t model, std::vector<cv::Rect_<double> >& o_regions, const cv::Mat_<uchar>& intensity, std::vector<double>& confidences);
	// The preference point allows for disambiguation if multiple faces are present (pick the closest one), if it is not set the biggest face is chosen
	bool _DetectSingleFaceHOG(size_t model, cv::Rect_<double>& o_region, const cv::Mat_<uchar>& intensity, double& confidence, const cv::Point preference = cv::Point(-1, -1));

	bool _DetectFacesVision(size_t model, std::vector<cv::Rect>& o_regions, const cv::Mat& img);
	bool _DetectSingleFaceVision(size_t model, cv::Rect& o_region, const cv::Mat& img, cv::Point preference);

	// Does the actual work - landmark detection
	bool _DetectLandmarks(const cv::Mat &color_img, const cv::Mat_<uchar> &gray_img, size_t face_id, bool force_validation);

	bool _DetectSingleModel(const cv::Mat &colorscale_image, const cv::Mat_<uchar> &grayscale_image, size_t model_id);
#ifndef SINGLE_MODEL_ONLY
	bool _DetectSingleModelWithBox(const cv::Mat &colorscale_image, const cv::Mat_<uchar> &grayscale_image, const cv::Rect_<double> bounding_box, size_t face_id);
	bool _DetectMultiModel(const cv::Mat &colorscale_image, const cv::Mat_<uchar> &grayscale_image);

	void _CheckModelDuplicate();
	float _CalculateFeatureDistance(std::vector<float> &a, std::vector<float> &b);
#endif

	void _NonOverlapingDetections(std::vector<cv::Rect_<double> >& face_detections);

	float _ComputeLength(cv::Point2f &pt1, cv::Point2f &pt2);
	void _ReCalculateFaceRect(size_t face_id);

	

	// init each face model
	void _modelInit();
  };
  //===========================================================================
}
#endif
