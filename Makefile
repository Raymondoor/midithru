TARGET = ./build/midithru.exe
CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lwinmm

SRC = src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Auto-detect OS
ifeq ($(OS),Windows_NT)
    RM = del /Q
    TARGET_FILE = $(subst /,\,$(TARGET))
else
    RM = rm -f
    TARGET_FILE = $(TARGET)
endif

clean:
	-$(RM) $(TARGET_FILE)

rebuild: clean all