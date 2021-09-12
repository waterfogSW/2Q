CXX			= g++
INC 		= -I${CURDIR}/include/
CXXFLAGS	= -g -std=c++11 $(INC)

SRCS_DIR	= src
SRCS		= $(wildcard $(SRCS_DIR)/*.cpp)
OBJS		= $(SRCS:.cpp=.o)

TARGET = src/main

all: $(TARGET)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(INC)

.PHONY : clean
clean:
	rm -rf $(TARGET)
