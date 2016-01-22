CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic 
LINKER = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

mp1 : main.o png.o rgbapixel.o
	$(LINKER) main.o png.o rgbapixel.o -lpng -o mp1
main.o : main.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) main.cpp
png.o : png.h
	$(CXX) $(CXXFLAGS) png.cpp
rgbapixel.o : rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp
clean: 
	rm -f *.o mp1