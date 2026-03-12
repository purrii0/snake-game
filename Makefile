CXX = g++
CXXFLAGS = -std=c++17 -O2
TARGET = yralib
SRC = src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) -lraylib -lm -lpthread -ldl -lrt -lX11

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
