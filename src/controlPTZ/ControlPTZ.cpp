#include "controlPTZ/ControlPTZ.hh"

using namespace std;
///\class ControlPTZ ControlPTZ.h "controlPTZ/ControlPTZ.h"
///\brief This class allows to manipulate the PTZ cameras.

///\sa ControlPTZ::ControlPTZ();
///\brief Constructor for the class "ControlPTZ". Once it is called, it will initialize curl.
ControlPTZ::ControlPTZ()
{
  //Curl configuration to work with HTTPS protocole
  handle=curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(handle, CURLOPT_USERPWD, "root:axis0");
  curl_easy_setopt(handle, CURLOPT_USERAGENT, "curl/7.21.6 (i686-pc-linux-gnu) libcurl/7.21.6 OpenSSL/1.0.0e zlib/1.2.3.4 libidn/1.22 librtmp/2.3");
  curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 1L);
  curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(handle, CURLOPT_HTTPAUTH, -17L); 
}

///\sa ControlPTZ::~ControlPTZ();
///\brief Desstructor for the class "ControlPTZ". Once it is called, it will cleanup curl.
ControlPTZ::~ControlPTZ()
{
  curl_easy_cleanup(handle);
}

///\sa void ControlPTZ::HTTPRequestPTZ(int pan, int tilt, int zoom, int cam);
///\brief This function of the class "ControlPTZ" will allow the camera to do a continuous move with a specified pan step, tilt step and zoom step.
///\param pan Input value of pan step.
///\param tilt Input value of tilt step.
///\param zoom Input value of zoom step.
///\param cam Input value to specify the camera (1 or 2).
void ControlPTZ::HTTPRequestPTZ(int pan, int tilt, int zoom, int cam)
{
  ostringstream oss;
  
  if (pan>100)
    pan=100;
  else if (pan<-100)
    pan=-100;
  
  if (tilt>100)
    tilt=100;
  else if (tilt<-100)
    tilt=-100;
  
  if (zoom>9999)
    zoom=9999;
	else if (zoom<-9999)
	  zoom=-9999;
  
  if (cam == 1 || cam == 2)
    {
      oss << "http://axis-ptz" << cam << "/axis-cgi/com/ptz.cgi?continuouspantiltmove=";
      oss << pan;
      oss << ",";
      oss << tilt;
      oss << "&rzoom=" << zoom;
      curl_easy_setopt(handle, CURLOPT_URL, oss.str().c_str());
      curl_easy_perform(handle);
    }
}

///\sa void ControlPTZ::HTTPRequestPTZPosRelative(float pan, float tilt, float zoom, int cam);
///\brief This function of the class "ControlPTZ" will allow the camera to go to a relative position with a specified pan step, tilt step and zoom step.
///\param pan Input value of pan step.
///\param tilt Input value of tilt step.
///\param zoom Input value of zoom step.
///\param cam Input value to specify the camera (1 or 2).
void ControlPTZ::HTTPRequestPTZPosRelative(float pan, float tilt, float zoom, int cam)
{
  ostringstream oss;
  
  if (pan>360)
    pan=360;
  else if (pan<-360)
    pan=-360;
  
  if (tilt>360)
    tilt=360;
  else if (tilt<-360)
    tilt=-360;
  
  if (zoom>9999)
    zoom=9999;
  else if (zoom<-9999)
    zoom=-9999;
  
  if (cam == 1 || cam == 2)
    {
      oss << "http://axis-ptz" << cam << "/axis-cgi/com/ptz.cgi?rpan=" << pan;
      oss << "&rtilt=" << tilt;
      oss << "&rzoom=" << zoom;
	    
      curl_easy_setopt(handle, CURLOPT_URL, oss.str().c_str());
      curl_easy_perform(handle);
    }
}

///\sa void ControlPTZ::HTTPRequestPTZPosAbsolute(float pan, float tilt, float zoom, int cam);
///\brief This function of the class "ControlPTZ" will allow the camera to go to an absolute position with a specified pan step, tilt step and zoom step.
///\param pan Input value of pan step.
///\param tilt Input value of tilt step.
///\param zoom Input value of zoom step.
///\param cam Input value to specify the camera (1 or 2).
void ControlPTZ::HTTPRequestPTZPosAbsolute(float pan, float tilt, float zoom, int cam)
{
  ostringstream oss;
  
  if (pan>180)
    pan=180;
  else if (pan<-180)
    pan=-180;
  
  if (tilt>180)
    tilt=180;
  else if (tilt<-180)
    tilt=-180;
  
  if (zoom>9999)
    zoom=9999;
  else if (zoom<-9999)
    zoom=-9999;
  
  if (cam == 1 || cam == 2)
    {
      oss << "http://axis-ptz" << cam << "/axis-cgi/com/ptz.cgi?pan=" << pan;
      oss << "&tilt=" << tilt;
      oss << "&zoom=" << zoom;
      
      curl_easy_setopt(handle, CURLOPT_URL, oss.str().c_str());
      curl_easy_perform(handle);
    }
}

void ControlPTZ::refreshPosition(double &pan, double &tilt, int &zoom, int cam)
{
	char buf[1235];
	const int port = 80;
	struct sockaddr_in sock_host;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	const char *queryposition = "GET /axis-cgi/com/ptz.cgi?query=position HTTP/1.1\n\n";
	
	// Création de l'adresse de la machine distante
	memset(& sock_host, '\0', sizeof(sock_host));
	sock_host.sin_family = AF_INET;
	sock_host.sin_port = htons(port);
	if (cam == 1)
		inet_aton("192.168.31.7", & sock_host.sin_addr);
	else if (cam == 2)
		inet_aton("192.168.31.8", & sock_host.sin_addr);
	else
		return;
	
	// Connexion sur l'adresse distante
	connect(sock, (struct sockaddr *) & sock_host, sizeof(sock_host));
	
	// Envoie du message sur le serveur
	if(write(sock, queryposition, strlen(queryposition)) == -1)
	{
		std::cout << "Error in writing on the server" << std::endl;
		return;
	}
	usleep(1000); // 100 ms
	if(read(sock,buf,1234) == -1)
	{
		std::cout << "Error in reading from the server" << std::endl;
		return;
	}
	close(sock);
	
	// Récupération des données
	int l,z;
	float p,t;
	char autofocus[3], autoiris[3];
	
	sscanf(buf, "HTTP/1.0 200 OK\nContent-Type: text/plain\nContent-Length: %d\n\npan=%f\ntilt=%f\nzoom=%d\nautofocus=%s\nautoiris=%s\n", 
	&l, &p, &t, &z, autofocus, autoiris);

	pan = p;
	tilt = t;
	zoom = z;
}

///\sa void ControlPTZ::HTTPRequestSetAutoFocus(bool b);
///\brief This function of the class "ControlPTZ" will allow both cameras to activate/deactivate the auto focus.
///\param b Input value. If it is true, the auto focus will be activated. Otherwise, it will be deactivated.
void ControlPTZ::HTTPRequestSetAutoFocus(bool b)
{
  ostringstream oss1, oss2;
  
  if (b)
    {
      oss1 << "http://axis-ptz1/axis-cgi/com/ptz.cgi?autofocus=on";
      oss2 << "http://axis-ptz2/axis-cgi/com/ptz.cgi?autofocus=on";
      
      curl_easy_setopt(handle, CURLOPT_URL, oss1.str().c_str());
      curl_easy_perform(handle);
      curl_easy_setopt(handle, CURLOPT_URL, oss2.str().c_str());
      curl_easy_perform(handle);
    } else {
    oss1 << "http://axis-ptz1/axis-cgi/com/ptz.cgi?autofocus=off";
    oss2 << "http://axis-ptz2/axis-cgi/com/ptz.cgi?autofocus=off";

    curl_easy_setopt(handle, CURLOPT_URL, oss1.str().c_str());
    curl_easy_perform(handle);
    curl_easy_setopt(handle, CURLOPT_URL, oss2.str().c_str());
    curl_easy_perform(handle);
  }
}

///\sa void ControlPTZ::HTTPRequestSetAutoIris(bool b);
///\brief This function of the class "ControlPTZ" will allow both cameras to activate/deactivate the auto iris.
///\param b Input value. If it is true, the auto iris will be activated. Otherwise, it will be deactivated.
void ControlPTZ::HTTPRequestSetAutoIris(bool b)
{
  ostringstream oss1, oss2;
	
  if (b)
    {
      oss1 << "http://axis-ptz1/axis-cgi/com/ptz.cgi?autoiris=on";
      oss2 << "http://axis-ptz2/axis-cgi/com/ptz.cgi?autoiris=on";

      curl_easy_setopt(handle, CURLOPT_URL, oss1.str().c_str());
      curl_easy_perform(handle);
      curl_easy_setopt(handle, CURLOPT_URL, oss2.str().c_str());
      curl_easy_perform(handle);
    } else {
    oss1 << "http://axis-ptz1/axis-cgi/com/ptz.cgi?autoiris=off";
    oss2 << "http://axis-ptz2/axis-cgi/com/ptz.cgi?autoiris=off";

    curl_easy_setopt(handle, CURLOPT_URL, oss1.str().c_str());
    curl_easy_perform(handle);
    curl_easy_setopt(handle, CURLOPT_URL, oss2.str().c_str());
    curl_easy_perform(handle);
  }
}

///\sa void ControlPTZ::HTTPRequestSetAutoIRCutFilter(bool b);
///\brief This function of the class "ControlPTZ" will allow both cameras to activate/deactivate the IR cut filter.
///\param b Input value. If it is true, the IR cut filter will be activated. Otherwise, it will be deactivated.
void ControlPTZ::HTTPRequestSetIRCutFilter(bool b)
{
  ostringstream oss1, oss2;
	
  if (b)
    {
      oss1 << "http://axis-ptz1/axis-cgi/com/ptz.cgi?ircutfilter=on";
      oss2 << "http://axis-ptz2/axis-cgi/com/ptz.cgi?ircutfilter=on";

      curl_easy_setopt(handle, CURLOPT_URL, oss1.str().c_str());
      curl_easy_perform(handle);
      curl_easy_setopt(handle, CURLOPT_URL, oss2.str().c_str());
      curl_easy_perform(handle);
    } else {
    oss1 << "http://axis-ptz1/axis-cgi/com/ptz.cgi?ircutfilter=off";
    oss2 << "http://axis-ptz2/axis-cgi/com/ptz.cgi?ircutfilter=off";

    curl_easy_setopt(handle, CURLOPT_URL, oss1.str().c_str());
    curl_easy_perform(handle);
    curl_easy_setopt(handle, CURLOPT_URL, oss2.str().c_str());
    curl_easy_perform(handle);
  }
}

///\sa void ControlPTZ::HTTPRequestSetAutoBackLight(bool b);
///\brief This function of the class "ControlPTZ" will allow both cameras to activate/deactivate the auto back light.
///\param b Input value. If it is true, the auto back light will be activated. Otherwise, it will be deactivated.
void ControlPTZ::HTTPRequestSetAutoBackLight(bool b)
{
  ostringstream oss1, oss2;
  
  if (b)
    {
      oss1 << "http://axis-ptz1/axis-cgi/com/ptz.cgi?backlight=on";
      oss2 << "http://axis-ptz2/axis-cgi/com/ptz.cgi?backlight=on";
      
      curl_easy_setopt(handle, CURLOPT_URL, oss1.str().c_str());
      curl_easy_perform(handle);
      curl_easy_setopt(handle, CURLOPT_URL, oss2.str().c_str());
      curl_easy_perform(handle);
    } else {
    oss1 << "http://axis-ptz1/axis-cgi/com/ptz.cgi?backlight=off";
    oss2 << "http://axis-ptz2/axis-cgi/com/ptz.cgi?backlight=off";
    
    curl_easy_setopt(handle, CURLOPT_URL, oss1.str().c_str());
    curl_easy_perform(handle);
    curl_easy_setopt(handle, CURLOPT_URL, oss2.str().c_str());
    curl_easy_perform(handle);
  }
}
