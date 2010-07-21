CC=g++
CFLAGS= 
CLIB=-lcv -lcxcore -lhighgui -lcvaux
INCLUDE=-I/usr/include/opencv
TARGET=/var/www/cgi-bin/
FLAGS=$(CFLAGS) $(INCLUDE)

PROGRAM=imgProcessServer

$(PROGRAM): soapC.o soapServer.o stdsoap2.o imgProcessServer.o
	$(CC) $(CFLAGS) $(CLIB) -o $(PROGRAM) soapC.o soapServer.o stdsoap2.o imgProcessServer.o
	chmod a+x $(PROGRAM)

soapC.o: soapC.cpp
	$(CC) $(FLAGS) -c soapC.cpp
soaphelloService.o:  soapServer.cpp
	$(CC) $(CFLAGS) -c soaphelloService.cpp

stdsoap2.o: stdsoap2.h stdsoap2.cpp
	$(CC) $(CFLAGS) -c stdsoap2.cpp

helloserver.o: imgProcessServer.cpp
	$(CC) $(CFLAGS) -c imgProcessServer.cpp

install:
	cp $(PROGRAM) $(TARGET)
clean:
	rm -rf *.o $(PROGRAM)

