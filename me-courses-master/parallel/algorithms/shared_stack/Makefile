CC = gcc

CFLAGS += -I./include
CFLAGS += -Wall -Wextra -Wpedantic -Wno-unused-parameter
CFLAGS += -g

LDFLAGS += -lm -lpthread

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = shared_stack

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
