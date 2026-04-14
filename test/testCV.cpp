#include "opencv2/core/cvdef.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

#define FACE_DETECT_FILE "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml"

using namespace std;
using namespace cv;

int main()
{
	CascadeClassifier faceCascade;
	if(!faceCascade.load(FACE_DETECT_FILE))
	{
		cerr << "testCV error: Unable to load cascade\n";
		return -1;
	}

	VideoCapture cap(0);
	cap.open(0, CAP_V4L2);
	if(!cap.isOpened())
	{
		std::cerr << "testCV error: Unable to open camera\n";
		return -1;
	}

	cap.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	cap.set(CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CAP_PROP_FRAME_HEIGHT, 720);
	cout << cap.get(CAP_PROP_FRAME_WIDTH) << " x "
     << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;

	Mat frame;
	for(;;)
	{
		cap >> frame;
		if(frame.empty())
		{
			std::cerr << "testCV error: Blank frame grabbed\n";
			break;
		}

		Mat grayscale;
		cvtColor(frame, grayscale, COLOR_BGR2GRAY);
		// Detecting Faces
		vector<Rect> faces;
		faceCascade.detectMultiScale(
				grayscale,
				faces,
				1.1,	// Scale Factor
				10,		// minNeighbors
				0,
				Size(30, 30)
				);

		for(const auto& face : faces)
		{
			rectangle(frame, face, Scalar(0, 255, 0), 2);
		}

		imshow("Live", frame);
		if(waitKey(1) >= 0) break;
	}

	return 0;
}
