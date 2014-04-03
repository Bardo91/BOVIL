################################################################################
# VISUAL TRACKIN UI MAKEFILE
#	Author: Pablo Ramón Soria
#	Date: 2013/11/22
################################################################################

########## Variables ##########
CXX = gcc
CPP_FILES := $(shell find ./../../source/ -name '*.cpp')
OBJ_FILES = $(patsubst %.cpp, %.o, $(CPP_FILES))

CXX_FLAGS = -fPIC -std=c++11 -g -O0 -Wall

########## EXTERNAL INCLUDES ##########
INCLUDES := -I./ -I/opt/ros/hydro/include
LIBRARIES := -L/opt/ros/hydro/lib
DEPENDENCIES := -lopencv_highgui -lopencv_core -lopencv_imgproc

########## RULES ##########

all: BOViL

rebuild: clean BOViL
	
# Remove preious files
clean:
	@echo "--------------------------------------"
	@echo "Cleaning project----------------------"
	rm -f $(OBJ_FILES)
	@echo "Project Cleaned-----------------------"


# Run application
run:
	./../../source/main

# Compile application
BOViL: $(OBJ_FILES)
	@echo "--------------------------------------"
	@echo "Current cpps--------------------------"
	@echo $(CPP_FILES)
	@echo "Searching for objects-----------------"
	@echo $(OBJ_FILES)
	@echo "Prepare compilation-------------------"
	$(CXX) $^ -o $@  $(INCLUDES) $(LIBRARIES) $(DEPENDENCIES) $(CXX_FLAGS)
	@echo "Generated file VisualTrackingUI-------"



# Compile to .o
%.o: %.cpp
	@echo "--------------------------------------"
	@echo "Linking " $^ " to " $@
	$(CXX) -c $^ -o $@ $(INCLUDES) $(LIBRARIES) $(DEPENDENCIES) $(CXX_FLAGS)


########## PHONY ##########
.PHONY: all clean run




