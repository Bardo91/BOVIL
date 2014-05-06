################################################################################
# VISUAL TRACKIN UI MAKEFILE
#	Author: Pablo Ramón Soria
#	Date: 2013/11/22
################################################################################

########## Variables ##########
CXX = g++
CPP_FILES := $(shell find ./../../src/ -name '*.cpp')
OBJ_FILES = $(patsubst %.cpp, %.o, $(CPP_FILES))

CXX_FLAGS = -fPIC -std=c++11 -O3 -Wall

########## EXTERNAL INCLUDES ##########
INCLUDES := -I./ -I../../../../library/source -I/usr/include
LIBRARIES := -L../../../../library/prj/linux -L/usr/lib
DEPENDENCIES := -lopencv_core -lopencv_highgui -lopencv_imgproc -lBOViL

########## RULES ##########

all: testImageAcquisition

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
testImageAcquisition: $(OBJ_FILES)
	@echo "--------------------------------------"
	@echo "Current cpps--------------------------"
	@echo $(CPP_FILES)
	@echo "Searching for objects-----------------"
	@echo $(OBJ_FILES)
	@echo "Prepare compilation-------------------"
	$(CXX) $^ -o $@  $(INCLUDES) $(LIBRARIES) $(DEPENDENCIES) $(CXX_FLAGS)
	@echo "Generated file testBOViLsegmentation-------"



# Compile to .o
%.o: %.cpp
	@echo "--------------------------------------"
	@echo "Linking " $^ " to " $@
	$(CXX) -c $^ -o $@ $(INCLUDES) $(LIBRARIES) $(DEPENDENCIES) $(CXX_FLAGS)


########## PHONY ##########
.PHONY: all clean run




