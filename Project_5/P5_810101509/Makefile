Compiler=g++ -std=c++20
BUILD_DIRECTORY=build

all: $(BUILD_DIRECTORY)/ImageEditor

$(BUILD_DIRECTORY)/ImageEditor: $(BUILD_DIRECTORY)/main.o $(BUILD_DIRECTORY)/bmp.o $(BUILD_DIRECTORY)/filterApp.o $(BUILD_DIRECTORY)/kernelFilter.o
	$(Compiler) $(BUILD_DIRECTORY)/main.o $(BUILD_DIRECTORY)/bmp.o $(BUILD_DIRECTORY)/filterApp.o $(BUILD_DIRECTORY)/kernelFilter.o -o $(BUILD_DIRECTORY)/ImageEditor

$(BUILD_DIRECTORY)/main.o: main.cpp bmp.cpp bmp.hpp changeColorFilter.hpp data.hpp Emboss.hpp filterApp.hpp filterApp.cpp gaussianBlur.hpp grayScale.hpp Invert.hpp kernelFilter.hpp kernelFilter.cpp Sharpen.hpp
	$(Compiler) -c main.cpp -o $(BUILD_DIRECTORY)/main.o

$(BUILD_DIRECTORY)/bmp.o: bmp.hpp bmp.hpp
	$(Compiler) -c bmp.cpp -o $(BUILD_DIRECTORY)/bmp.o

$(BUILD_DIRECTORY)/kernelFilter.o: kernelFilter.hpp kernelFilter.cpp filterApp.hpp filterApp.cpp data.hpp bmp.hpp bmp.cpp
	$(Compiler) -c kernelFilter.cpp -o $(BUILD_DIRECTORY)/kernelFilter.o

$(BUILD_DIRECTORY)/filterApp.o: filterApp.cpp filterApp.hpp data.hpp bmp.hpp bmp.cpp
	$(Compiler) -c filterApp.cpp -o $(BUILD_DIRECTORY)/filterApp.o

clean:
	rm -rf $(BUILD_DIRECTORY)/ && mkdir $(BUILD_DIRECTORY)

