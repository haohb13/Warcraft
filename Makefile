INC_DIR :=  ./
SRC_DIR = ./
#EXE_DIR := ./bin
CC := g++
CPPFLAGS := -std=c++11 -g -Wno-deprecated
LIBS := -llog4cpp -lpthread
INC_FILE := $(addprefix -I, $(INC_DIR))
#CPP_FILE :=  $(wildcard ./src/utils/*.cpp) $(wildcard ./src/network/*.cpp) $(wildcard ./src/*.cpp)
CPP_FILE :=  $(wildcard ./*.cc) 
OBJS := $(patsubst %.cc, %.o, $(CPP_FILE))
objs:=$(addsuffix /*.o, $(SRC_DIR))
TARGET := wow.exe
$(TARGET):$(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^ $(INC_FILE) $(LIBS)
#%.o:%.cpp
%.o:%.cc
	$(CC) $(CPPFLAGS) -o $@ -c $< $(INC_FILE) $(LIBS)
object:
	@echo $(objs)
clean:
	rm -rf $(TARGET) $(OBJS)
