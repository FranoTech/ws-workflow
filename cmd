#!/bin/bash
g++ `pkg-config opencv --cflags` `pkg-config opencv --libs` -fopenmp -o maliServer maliServer.cpp soapC.cpp soapServer.cpp stdsoap2.cpp
#g++ `pkg-config opencv --cflags` `pkg-config opencv --libs` -o maliServer maliServer.cpp soapC.cpp soapServer.cpp stdsoap2.cpp
echo "***compiled***"
sudo chmod a+x maliServer
echo "***gived a+x***"
sudo cp maliServer /var/www/cgi-bin/
echo "***copied maliServer***"
sudo cp mali.wsdl /var/www/
echo "***copied mali.wsdl***"
