################################################################################
# BOViL MAKEFILE
#	Author: Pablo Ramón Soria
#	Date: 2014-09-04
################################################################################

########## Variables ##########
CXX = g++
CPP_FILES := $(shell find ./../../source/ -name '*.cpp')
OBJ_FILES = $(patsubst %.cpp, %.o, $(CPP_FILES))

CXX_FLAGS = -fPIC -std=c++11 -g -O0 -Wall

########## EXTERNAL INCLUDES ##########
INCLUDES := -I./ -I ../../../../library/source
LIBRARIES := -L ../../../../library/prj/linux
DEPENDENCIES := -lBOViL

########## RULES ##########

all: test

rebuild: clean test
	
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
test: $(OBJ_FILES)
	@echo "--------------------------------------"
	@echo "Current cpps--------------------------"
	@echo $(CPP_FILES)
	@echo "Searching for objects-----------------"
	@echo $(OBJ_FILES)
	@echo "Prepare Linking-------------------"
	$(CXX) $^ -o $@  $(INCLUDES) $(LIBRARIES) $(DEPENDENCIES) $(CXX_FLAGS)
	@echo "Generated file -------"



# Compile to .o
%.o: %.cpp
	@echo "--------------------------------------"
	@echo "Compiling " $^ " to " $@
	$(CXX) -c $^ -o $@ $(INCLUDES) $(LIBRARIES) $(DEPENDENCIES) $(CXX_FLAGS)


########## PHONY ##########
.PHONY: all clean run




