#ifndef CV_HPP
#define CV_HPP

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include "opencv2/core/cvdef.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/objdetect/face.hpp"
#include "opencv2/videoio.hpp"

#define MODEL_PATH "/home/tzcao/Documents/2-Personal_Projects/annoyingAlarmClock/assets/cvModels/face_detection_yunet_2023mar.onnx"

using namespace cv;
// face vector index labels
typedef enum faceIndices
{
	face_x1 = 0,
	face_y1,
	face_width,
	face_height,
	face_x_right_eye,
	face_y_right_eye,
	face_x_left_eye,
	face_y_left_eye,
	face_x_nose_tip,
	face_y_nose_tip,
	// can add face_x_right_corner_mouth... etc if needed
} faceIndices;

int InitCamera(Ptr<FaceDetectorYN> &detector, VideoCapture& capture, int cameraID = 0, int frameWidth = 1280, int frameHeight = 720, String FOURCC = "MJPG");
#endif
