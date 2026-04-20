#include "CV.hpp"
#include <iostream>
#include "opencv2/objdetect/face.hpp"
#include "opencv2/videoio.hpp"

using namespace std;
using namespace cv;


int InitCamera(Ptr<FaceDetectorYN> &detector, cv::VideoCapture& capture, int cameraID = 0, int frameWidth = 1280, int frameHeight = 720, String FOURCC = "MJPG")
{
	detector = FaceDetectorYN::create(MODEL_PATH, "", Size(frameWidth, frameHeight)); 

	capture.open(cameraID, CAP_V4L2);
	if(!capture.isOpened())
	{
		cerr << "CV error: InitCamera: Unable to open Camera\n";
		return -1;
	}

	if(FOURCC.size() != 4)
	{
		cerr << "CV error: InitCamera: FOURCC must be 4 characters\n";
		return -1;
	}

	capture.set(CAP_PROP_FOURCC, CV_FOURCC(FOURCC[0], FOURCC[1], FOURCC[2], FOURCC[3]));
	capture.set(CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CAP_PROP_FRAME_HEIGHT, 720);

	detector->setInputSize(Size(frameWidth, frameHeight));

	return 0;
}
