################################################################################
# VISUAL TRACKIN UI MAKEFILE
#	Author: Pablo Ramón Soria
#	Date: 2013/11/22
################################################################################

########## Variables ##########
CXX = g++
CPP_FILES := $(shell find ./../../source/ -name '*.cpp')
OBJ_FILES = $(patsubst %.cpp, %.o, $(CPP_FILES))

##CXX_FLAGS = -fPIC -std=c++11 -g -O0 -Wall
CXX_FLAGS = -fPIC -std=c++11 -O3 -Wall -Werror

########## EXTERNAL INCLUDES ##########
INCLUDES := -I./ 
LIBRARIES := 
DEPENDENCIES :=

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

# Compile static library
static_lib: $(OBJ_FILES)
	@echo "--------------------------------------"
	@echo "Current cpps--------------------------"
	@echo $(CPP_FILES)
	@echo "Searching for objects-----------------"
	@echo $(OBJ_FILES)
	@echo "Prepare compilation-------------------"
	ar rcs libBOViL.a $^
	@echo "Generated static library -------------"

# Compile shared library
shared_lib: $(OBJ_FILES)
	@echo "--------------------------------------"
	@echo "Current cpps--------------------------"
	@echo $(CPP_FILES)
	@echo "Searching for objects-----------------"
	@echo $(OBJ_FILES)
	@echo "Prepare compilation-------------------"
	gcc -shared -o libBOViL.so $(OBJ_FILES)
	@echo "Generated shared library -------------"



# Compile to .o
%.o: %.cpp
	@echo "--------------------------------------"
	@echo "Linking " $^ " to " $@
	$(CXX) -c $^ -o $@ $(INCLUDES) $(LIBRARIES) $(DEPENDENCIES) $(CXX_FLAGS)


########## PHONY ##########
.PHONY: all clean run




