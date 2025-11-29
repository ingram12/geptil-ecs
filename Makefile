CC ?= cc
BUILD_DIR := build
BIN := $(BUILD_DIR)/geptil-ecs
SRC := $(shell find src -name '*.c')
OBJ := $(patsubst src/%, $(BUILD_DIR)/%, $(SRC:.c=.o))
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -Iinclude

ifeq ($(DEBUG),1)
CFLAGS += -O0 -g -fsanitize=address,undefined -fno-omit-frame-pointer
else
CFLAGS += -O2 -march=native
endif

.PHONY: all run clean help

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN)

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Usage: make [target] [DEBUG=1]"
	@echo "Targets: all (default), run, clean, help"
