CC      = gcc
CFLAGS  = -Wall -Wextra -g -Iinclude -Itests

ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM  = del /Q /F
else
    EXE =
    RM  = rm -f
endif

TARGET   = biblioteca$(EXE)

SRC      = $(wildcard src/*.c)
MAIN     = main/main.c
TEST_SRC = tests/teste.c
HEADERS  = $(wildcard include/*.h) $(wildcard tests/*.h)

all: build test run

build: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC) $(MAIN) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) $(TEST_SRC) $(MAIN) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) --teste

clean:
	-$(RM) $(TARGET)

.PHONY: all build run test clean