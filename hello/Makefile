CC=g++
CFLAGS= -fopenmp
PROGRAM=hello
TARGET=/var/www/cgi-bin/


$(PROGRAM): soapC.o soaphelloService.o stdsoap2.o helloserver.o
	$(CC) $(CFLAGS) -o $(PROGRAM) soapC.o soaphelloService.o stdsoap2.o helloserver.o
	chmod a+x $(PROGRAM)

soapC.o: soapC.cpp
	$(CC) $(CFLAGS) -c soapC.cpp
soaphelloService.o: soaphelloService.h soaphelloService.cpp
	$(CC) $(CFLAGS) -c soaphelloService.cpp

stdsoap2.o: stdsoap2.h stdsoap2.cpp
	$(CC) $(CFLAGS) -c stdsoap2.cpp

helloserver.o: helloserver.cpp
	$(CC) $(CFLAGS) -c helloserver.cpp

install:
	cp $(PROGRAM) $(TARGET)
clean:
	rm -rf *.o $(PROGRAM)

