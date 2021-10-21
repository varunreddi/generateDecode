# build hellocpp executable when user executes "make"

CXX	= g++
#SRCS	= $(wildcard *.cpp) $(wildcard *.c)  DecodeTestIE  Decode_NAS_Messages
SRC = Decode_NAS_Messages
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


#g++ -I ../include -fPIC -c Decode_NAS_Messages.cpp 	
#g++ -o reg Decode_NAS_Messages.o  ../lib/libnascodec.a
