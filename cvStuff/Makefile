CXX = g++
INCLUDES = -I/usr/include/opencv4 -I/usefulConsts.hpp
CFLAGS = -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_objdetect -lopencv_imgcodecs -g

cvTest: testCV.cpp
	$(CXX) testCV.cpp -o test $(INCLUDES) $(CFLAGS)

repurpose: repurposedCV.cpp
	$(CXX) repurposedCV.cpp -o yo $(INCLUDES) $(CFLAGS)

clean:
	rm -rf test *.o yo
