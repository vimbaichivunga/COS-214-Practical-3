CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g
TARGET   := eventflow

SOURCES  := $(wildcard *.cpp)
OBJECTS  := $(SOURCES:.cpp=.o)

.PHONY: all clean docs

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

docs:
	doxygen Doxyfile

clean:
	rm -f *.o $(TARGET)
	rm -rf docs/html docs/latex
