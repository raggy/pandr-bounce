CC=g++
LDLIBS=-lglut -lasound -lpthread
CXXFLAGS=-D__LINUX_ALSASEQ__
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bounce

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDLIBS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) -c $(CXXFLAGS) $< -o $@

clean: $(OBJECTS)
	rm -f $(OBJECTS) $(EXECUTABLE)
