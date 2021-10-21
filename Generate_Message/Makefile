# build hellocpp executable when user executes "make"

CXX	= g++
#SRCS	= $(wildcard *.cpp) $(wildcard *.c)
SRC = PDU_session_modification_request_generation
TARGET	= reg
LIBS	= -lnascodec
LIB_DIRS = -L../OAI/lib
INC	= -I../OAI/include

all	: hello
	$(CXX) -o $(TARGET) ${SRC}.o $(LIB_DIRS) $(LIBS)
	rm -f *.o
	
hello	:
	$(CXX) $(INC) -fPIC -c ${SRC}.cpp
	
clean	:
	rm -f $(TARGET)
	rm -f *.o
	
#provide argument to the executable as command line arguments are used inside the generation code.


#g++ -I ../../include -fPIC -c Authentication_failure_generation.cpp 
#g++ -o reg Authentication_failure_generation.o  ../../lib/libnascodec.a

