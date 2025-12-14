CC ?= cc
BUILD_DIR := build
BIN := $(BUILD_DIR)/geptil-ecs

# Find all .c files in src (including subdirectories)
SRC := $(shell find src -name '*.c')

# Transform src/.../file.c -> build/.../file.o
OBJ := $(patsubst src/%, $(BUILD_DIR)/%, $(SRC:.c=.o))

# Compilation flags
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -Iinclude

# Flags for generating dependency files
DEPFLAGS := -MMD -MP

# Sanitizer flags (used only when DEBUG=1)
SANITIZERS := -fsanitize=address,undefined

# LDFLAGS for the linker
LDFLAGS :=

ifeq ($(DEBUG),1)
CFLAGS += -O0 -g -fno-omit-frame-pointer $(SANITIZERS)
LDFLAGS += $(SANITIZERS)
else
CFLAGS += -O2 -march=native
endif

# Add DEPFLAGS to CFLAGS so each .o has a .d
CFLAGS += $(DEPFLAGS)

.PHONY: all run clean help

all: $(BIN)

# Linking: use LDFLAGS (including sanitizers if enabled)
$(BIN): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Rule to build object files (preserve directory structure)
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN)

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Usage: make [target] [DEBUG=1]"
	@echo "Targets: all (default), run, clean, help"

# Include all automatically generated dependency files (.d).
# Use wildcard to avoid errors if a .d file does not exist yet.
-include $(wildcard $(OBJ:.o=.d))
