SRC_FILES := $(wildcard ./*.cpp)

BUILD_MODE ?= RELEASE

ifeq ($(BUILD_MODE),DEBUG)
    OPTIMISE_FLAG = -g -O0
else
    OPTIMISE_FLAG = -s -O1
endif

default:
	g++ $(SRC_FILES) -o output.exe $(OPTIMISE_FLAG) -std=c++17 -Wall -static-libstdc++ -Wno-missing-braces -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm