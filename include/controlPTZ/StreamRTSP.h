#ifndef STREAMRTSP_H
#define STREAMRTSP_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace cv;

class StreamRTSP
{
	public :
	  StreamRTSP(string pathRTSP, int fps=-1,  bool iplImage=false);
	  StreamRTSP(int device=0);
	  ~StreamRTSP();
	  IplImage *grabIplFrame();
	  Mat grabFrame();

	private :
	  CvCapture *cvCap;
	  IplImage *currentFrame;

	  VideoCapture vcap;
	  Mat matCurrentFrame;
	  Mat matLastFrame;
	  int fps;
	  
	  bool iplImage;
};

#endif
