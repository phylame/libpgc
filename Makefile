
TARGET = libxgc
VPATH = src
INCLUDE = include
BUILDDIR = build

# compiler flags
CFLAGS = -Wall -g

# include
CPPFLAGS = -I$(INCLUDE)

# lib
LIBS = -lc

OBJS = xgc.o list.o

all: share

$(TARGET): $(OBJS)
	mkdir lib 2>&1 > /dev/null
	$(CC) -o $(TARGET) $^

share:


static:


clean:
	rm $(OBJS)
