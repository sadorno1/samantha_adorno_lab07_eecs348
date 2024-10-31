CXX = g++
CXXFLAGS = -std=c++11
TARGET = lab07
SRCS = lab07.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)