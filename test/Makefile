CXX = g++
INCLUDES = -I/usr/include/opencv4
CFLAGS = -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc

cvTest: testCV.cpp
	$(CXX) testCV.cpp -o test $(INCLUDES) $(CFLAGS)

clean:
	rm -rf test *.o
