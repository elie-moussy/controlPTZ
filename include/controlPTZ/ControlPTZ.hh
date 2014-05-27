#ifndef CONTROLPTZ_H
#define CONTROLPTZ_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
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
  // Get pan, tilt and zoom from the camera
  void refreshPosition(double &pan, double &tilt, int &zoom, int cam=1);
 private :
  CURL *handle;
};

#endif
