#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include "./usefulConsts.hpp"
#include "opencv2/core/cvdef.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/objdetect/face.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>

#define MODEL_PATH "./models/face_detection_yunet_2023mar.onnx"
#define SCORE_THRESH	0.9		// filter out faces of score < SCORE_THRESH
#define NMS_THRESH		0.3		// Suppress bounding boxes of iou >= NMS_THRESH
#define TOP_K			5000	// Keep top_k bounding boxes before NMS

using namespace cv;
using namespace std;

static void visualize(Mat &input, int frame, Mat& faces, int thickness = 2)
{
	if(frame >= 0)
		cout << "Frame " << frame << ", ";

	// Print out parameters:
	cout 
		<< "top-left coords: (" << faces.at<float>(face_x1) << ", " << faces.at<float>(face_y1) << "), "
		 << "box width: " << faces.at<float>(face_width) << ", box height: " << faces.at<float>(face_height)
		 << ", score: " << cv::format("%.2f", faces.at<float>(14)) << "\n\n";

	// Draw box
	rectangle(input, Rect2i(int(faces.at<float>(face_x1)), int(faces.at<float>(face_y1)), int(faces.at<float>(face_width)), int(faces.at<float>(face_height))), Scalar(255, 0, 0), thickness);
}

int main(int argc, char** argv)
{
	Ptr<FaceDetectorYN> detector = FaceDetectorYN::create(MODEL_PATH, "", Size(1280, 720)); // use mostly defaults
	
	// take image from webcam
	int frameWidth, frameHeight;
	VideoCapture capture;

	capture.open(0, CAP_V4L2);
	if(!capture.isOpened())
	{
		std::cerr << "repurposedCV error: Unable to open Camera\n";
		return -1;
	}

	capture.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	capture.set(CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CAP_PROP_FRAME_HEIGHT, 720);
	frameWidth = capture.get(CAP_PROP_FRAME_WIDTH);
	frameHeight = capture.get(CAP_PROP_FRAME_HEIGHT);

	cout << "Video: width=" << frameWidth
		<< ", height=" << frameHeight 
		<< endl;

	detector->setInputSize(Size(frameWidth, frameHeight));

	int nFrame = 0;
	for(;;)
	{
		Mat frame;
		if(!capture.read(frame) || frame.empty())
		{
			std::cerr << "repurposedCV error: FAILED TO GRAB FRAME\n";
			break;
		}
		resize(frame, frame, Size(frameWidth, frameHeight));

		Mat faces;
		detector->detect(frame, faces);

		// even if no face detected, KEEP GOING!
		if(faces.empty() || faces.rows == 0)
		{
			cout << "Frame " << nFrame << ": No Face Detected\n\n";
			imshow("Live", frame);

			++nFrame;
			waitKey(1);
			continue;
		}

		Mat result = frame.clone();
		visualize(result, nFrame, faces);

		imshow("Live", result);

		++nFrame;

		if(waitKey(1)) break;
	}
	
	return 0;
}
