CXX = g++
CXXFLAGS = -Iinclude -Iinclude/DataStructures -Wall
SRC = main.cpp src/Document.cpp src/Index.cpp src/SearchEngine.cpp src/Tokenizer.cpp src/DataStructures/IndexNode.cpp src/DataStructures/LinkedList.cpp
TARGET = main.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	del $(TARGET)
