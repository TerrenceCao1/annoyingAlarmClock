#include "opencv2/core/cvdef.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
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
		imshow("Live", frame);
		if(waitKey(1) >= 0) break;
	}

	return 0;
}
