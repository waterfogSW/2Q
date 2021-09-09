CXX			= g++
INC 		= -I${CURDIR}/include/
CXXFLAGS	= -g -std=c++11 $(INC)

SRCS_DIR	= src
SRCS		= $(wildcard $(SRCS_DIR)/*.cpp)
OBJS		= $(SRCS:.cpp=.o)

TARGET = main

.c.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(TARGET) : $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

all: $(TARGET)

dep : 
	gccmaedep $(INC) $(SRCS)

.PHONY : clean
clean:
	rm -rf $(TARGET) $(OBJS)
