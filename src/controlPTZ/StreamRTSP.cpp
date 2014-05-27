#include "controlPTZ/StreamRTSP.hh"

using namespace std;

///\class StreamRTSP StreamRTSP.h "controlPTZ/StreamRTSP.h"
///\brief This class allows to grab a frame from a device.

///\sa StreamRTSP::StreamRTSP(string pathRTSP, int fps, bool iplImage);
///\brief The constructor of the class "StreamRTSP".
///\param pathRTSP Input value of the stream path.
///\param fps Input value of the number of frames per second.
///\param iplImage Input value. If "iplImage" is true, we use the old version of opencv in order to handle the frame. Otherwise, we use the new version of opencv.
StreamRTSP::StreamRTSP(string pathRTSP, int fps, bool iplImage)
{
  this->iplImage=iplImage;

  ostringstream oss;
  oss << pathRTSP;
  if (fps != -1)
    {
      oss << "?fps=" << fps;
      this->fps=fps;
    }
	
  cout << "Open the stream (this might take several minutes...)\nWait the frame window" << endl;
	
  if (this->iplImage)
    {
      cvCap=cvCaptureFromFile(oss.str().c_str());

      if(cvCap==NULL)
	{
	  cout << "Error opening video stream or file" << endl;
	}
      currentFrame = this->grabIplFrame();
    }
  else
    {
      vcap.open(oss.str().c_str());
      matCurrentFrame = this->grabFrame();
    }	
}

///\sa StreamRTSP::StreamRTSP(int device);
///\brief The constructor of the class "StreamRTSP".
///\param device Input value that specifies the device from which the frame should be grabed.
StreamRTSP::StreamRTSP(int device)
{
  vcap.open(device);
  this->iplImage=false;
  matCurrentFrame = this->grabFrame();
}

///\sa StreamRTSP::StreamRTSP(int device);
///\brief The desstructor of the class "StreamRTSP".
StreamRTSP::~StreamRTSP()
{
  if (this->iplImage)
    cvReleaseCapture(&cvCap);
}

///\sa IplImage *StreamRTSP::grabIplFrame();
///\brief This function of the class "StreamRTSP" allows to grab a frame from a device.
///\return This function will return the frame grabbed via an IplImage pointer (old version of opencv).
IplImage *StreamRTSP::grabIplFrame()
{

  currentFrame=cvQueryFrame(cvCap);
  if (!currentFrame)
    {
      cout << "StreamRTSP : grab frame error" << endl;
    }
  return currentFrame;
}

///\sa Mat *StreamRTSP::grabFrame();
///\brief This function of the class "StreamRTSP" allows to grab a frame from a device.
///\return This function will return the frame grabbed via an opencv matrix (new version of opencv).
Mat StreamRTSP::grabFrame()
{

  if (!vcap.read(matCurrentFrame))
    {
      cout << "StreamRTSP : grab frame error" << endl;
    }
  else
    {
      matLastFrame=matCurrentFrame;
    }
  return matLastFrame;
}

