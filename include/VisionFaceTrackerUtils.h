///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017, Hann, Tsinghua University
// A branch of OpenFace Framework which uses KCF to stabilize face detection,
//     alignment, and feature extration.
// Utils to get cmd args and to draw detection results.
///////////////////////////////////////////////////////////////////////////////

#ifndef __VISION_FACE_TRACKER_UTILS_h_
#define __VISION_FACE_TRACKER_UTILS_h_

#if defined(_MSC_VER)  
#define JL_SIZE_T_SPECIFIER "%Iu"  
#define JL_SSIZE_T_SPECIFIER "%Id"  
#define JL_PTRDIFF_T_SPECIFIER "%Id"  
#elif defined(__GNUC__)  
#define JL_SIZE_T_SPECIFIER "%zu"  
#define JL_SSIZE_T_SPECIFIER "%zd"  
#define JL_PTRDIFF_T_SPECIFIER "%zd"  
#else // TODO figure out which to use.  
#if NUMBITS == 32  
#define JL_SIZE_T_SPECIFIER something_unsigned  
#define JL_SSIZE_T_SPECIFIER something_signed  
#define JL_PTRDIFF_T_SPECIFIER something_signed  
#else  
#define JL_SIZE_T_SPECIFIER something_bigger_unsigned  
#define JL_SSIZE_T_SPECIFIER something_bigger_signed  
#define JL_PTRDIFF_T_SPECIFIER something-bigger_signed  
#endif  
#endif  

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

namespace vision
{
	VISION_FACE_TRACKER_API void Draw(cv::Mat img, const std::vector<VisionFaceTrackingInfo>& models);

}
#endif
