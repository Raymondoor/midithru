
# Detect OS
ifeq ($(OS),Windows_NT)
    TARGET = ./build/midithru.exe
    SRC = src/main_win.c
    LDFLAGS = -lwinmm
    RM = del /Q
    TARGET_FILE = $(subst /,\,$(TARGET))
else
    TARGET = ./build/midithru
    SRC = src/main_linux.c
    LDFLAGS = -lasound
    RM = rm -f
    TARGET_FILE = $(TARGET)
endif

CC = gcc
CFLAGS = -Wall -O2

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	-$(RM) $(TARGET_FILE)

rebuild: clean all