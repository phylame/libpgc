TARGET = test_list
OBJS = xgc.o list.o test_list.o

VPATH = ../src
CPPFLAGS = -I../include

$(ALL): $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $^

clean:
	rm $(TARGET) $(OBJS)
