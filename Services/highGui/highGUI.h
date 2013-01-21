//gsoap ns service name: highGUI
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/highGUI.wsdl
//gsoap ns service location: http://localhost/cgi-bin/highGUIServer

//gsoap ns schema namespace: urn:gui

class ns__base64Binary
{ unsigned char *__ptr;
  int __size;
};


//gsoap ns service method-documentation: imRead Convert Image to Mat data (CV_8UC1 gray scale image is default)
int ns__imRead(std::string InputMatFilename, int flag=0, std::string &OutputMatFilename);

//gsoap ns service method-documentation: imWrite Saving Mat to JPG image
int ns__imWrite ( std::string InputMatFilename, std::string fileExtension, std::string &OutputMatFilename);

//gsoap ns service method-documentation: viewImage View an image in workbench
int ns__viewImage( std::string InputMatFilename, ns__base64Binary &image);
