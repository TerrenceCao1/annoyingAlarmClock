#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <thread>
#include <atomic>
#include "CV.hpp"
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include "opencv2/core/cvdef.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/objdetect/face.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Ptr<FaceDetectorYN> detector;
	VideoCapture capture;

	InitCamera(detector, capture);
	for(;;)
	{
		Mat frame;
		if(!capture.read(frame) || frame.empty())
		{
			std::cerr << "Empty Frame\n";
			break;
		}

		imshow("Live", frame);
		if(waitKey(1) == 'q') break;
	}

	capture.release();
	destroyAllWindows();
	return 0;
}
