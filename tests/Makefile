CC          = $(CROSS_COMPILE)g++
CXXFLAGS    = -Wall -O2 -I../
LDFLAGS     = -lgtest -pthread
SRCS        = $(notdir $(wildcard *.cpp))
OBJS        = $(SRCS:.cpp=.o)
TARGET      = testAll

.PHONY: clean all
all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp %.h
	$(CC) -c $< $(CXXFLAGS)
