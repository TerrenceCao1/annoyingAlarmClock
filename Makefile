CXX 			= g++
INCLUDES 		= -I/usr/include/opencv4 -I./inc
CFLAGS 			= -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_objdetect -lopencv_imgcodecs -g

MAIN 			= main
MAINSRC			= $(MAIN).cpp
SRCS			= $(wildcard src/*.cpp)

main: ./src/main.cpp
	$(CXX) $(SRCS) $(INCLUDES) $(CFLAGS) -o $(MAIN)

clean:
	rm -rf test *.o
