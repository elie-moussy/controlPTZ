#ifndef CONTROLPTZ_H
#define CONTROLPTZ_H

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>

class ControlPTZ
{
 public:
  ControlPTZ();

  ~ControlPTZ();
  //speed control (zoom still controlled in relative position mode)
  void HTTPRequestPTZ(int pan=0, int tilt=0, int zoom=0, int cam=1);
  //relative position control
  void HTTPRequestPTZPosRelative(float pan=0, float tilt=0, float zoom=0, int cam=1);
  //absolute position control
  void HTTPRequestPTZPosAbsolute(float pan=0, float tilt=0, float zoom=0, int cam=1);
  // Set auto focus
  void HTTPRequestSetAutoFocus(bool b);
  // Set auto iris
  void HTTPRequestSetAutoIris(bool b);
  // Set IR cut filter
  void HTTPRequestSetIRCutFilter(bool b);
  // Set auto back light compensation
  void HTTPRequestSetAutoBackLight(bool b);
  
 private :
  CURL *handle;
};

#endif
