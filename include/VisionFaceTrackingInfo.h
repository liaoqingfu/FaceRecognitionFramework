///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017, Hann, Tsinghua University
// A branch of OpenFace Framework which uses KCF to stabilize face detection,
//     alignment, and feature extration.
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __VISION_FACE_MODEL_h_
#define __VISION_FACE_MODEL_h_

#include <vector>

// OpenCV dependencies
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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

namespace vision
{
	class VisionFaceTracker;

	class VISION_FACE_TRACKER_API VisionFaceTrackingInfo
	{
	public:
		friend class VisionFaceTracker;
		enum FaceModelStatus { ACTIVE, LOST, INACTIVE, UNKNOWN  };
		
		VisionFaceTrackingInfo();
		VisionFaceTrackingInfo(const VisionFaceTrackingInfo &other);
		~VisionFaceTrackingInfo() {}

		VisionFaceTrackingInfo & operator= (const VisionFaceTrackingInfo& other);

		int getFakeID() const
		{
			return _fake_id;
		}

		cv::Rect getBoundingBox() const
		{
			return _boundingbox;
		}

		FaceModelStatus getFaceModelStatus() const
		{
			if (_active)
			{
				if (_detection_success)
					return VisionFaceTrackingInfo::ACTIVE;
				else
					if (_failures_in_a_row > -1)
						return VisionFaceTrackingInfo::LOST;
					else
						return VisionFaceTrackingInfo::UNKNOWN;
			}
			else
				return VisionFaceTrackingInfo::INACTIVE;
		}

	protected:
		int _fake_id;

		bool _active;
		// Indicating if landmark detection succeeded
		bool _detection_success;
		// Keeping track of how many frames the tracker has failed in so far when tracking in videos
		// This is useful for knowing when to initialise and reinitialise tracking
		int _failures_in_a_row;

		cv::Rect _boundingbox;
	};

	class VISION_FACE_TRACKER_API VisionAlignedFace
	{
	public:
		cv::Mat img;
		int64 timestamp;

		VisionAlignedFace() : timestamp(0)
		{
		}

		VisionAlignedFace(const cv::Mat &img, int64 t) : timestamp(t)
		{
			this->img = img.clone();
		}

		VisionAlignedFace(const VisionAlignedFace &other) : timestamp(other.timestamp)
		{
			img = other.img.clone();
		}

#ifdef USE_CPP11_STD
		VisionAlignedFace(const VisionAlignedFace &&other) : timestamp(other.timestamp)
		{
			img = other.img;
		}
#endif

        VisionAlignedFace & operator= (const VisionAlignedFace& other)
        {
            timestamp = other.timestamp;
            img = other.img.clone();
			return *this;
        }

#ifdef USE_CPP11_STD
        VisionAlignedFace & operator= (const VisionAlignedFace&& other)
        {
            timestamp = other.timestamp;
            img = other.img;
			return *this;
        }
#endif

	};

}

#endif
