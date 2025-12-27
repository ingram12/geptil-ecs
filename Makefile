CC ?= cc
BUILD_DIR := build
BIN := $(BUILD_DIR)/geptil-ecs
LDFLAGS = -framework Cocoa -framework QuartzCore -L${VULKAN_SDK}/lib -lvulkan -Wl,-rpath,${VULKAN_SDK}/lib -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw -Wl,-rpath,/opt/homebrew/Cellar/glfw/3.4/lib -L/opt/homebrew/opt/freetype/lib -lfreetype
INCLUDES = -Iinclude -I$(VULKAN_SDK)/include -I/opt/homebrew/Cellar/glfw/3.4/include

# Find all .c files in src (including subdirectories)
SRC := $(shell find src -name '*.c')

# Transform src/.../file.c -> build/.../file.o
OBJ := $(patsubst src/%, $(BUILD_DIR)/%, $(SRC:.c=.o))

# Compilation flags
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic $(INCLUDES)

# Flags for generating dependency files
DEPFLAGS := -MMD -MP

# Sanitizer flags (used only when DEBUG=1)
SANITIZERS := -fsanitize=address,undefined

# 📜 Shaders
SHADER_DIR = src/include/vulkan/shader
SHADER_SRC = $(wildcard $(SHADER_DIR)/*.vert) $(wildcard $(SHADER_DIR)/*.frag)
SHADER_SPV = $(SHADER_SRC:%=%.spv)

# Shader compilation
$(SHADER_DIR)/%.spv: $(SHADER_DIR)/%
	glslangValidator -V $< -o $@

ifeq ($(DEBUG),1)
CFLAGS += -O0 -g -fno-omit-frame-pointer $(SANITIZERS)
LDFLAGS += $(SANITIZERS)
else
CFLAGS += -O2 -march=native
endif

# Add DEPFLAGS to CFLAGS so each .o has a .d
CFLAGS += $(DEPFLAGS)

.PHONY: all run clean help

all: $(BIN) $(SHADER_SPV)

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
	rm -f $(SHADER_SPV)

help:
	@echo "Usage: make [target] [DEBUG=1]"
	@echo "Targets: all (default), run, clean, help"

# Include all automatically generated dependency files (.d).
# Use wildcard to avoid errors if a .d file does not exist yet.
-include $(wildcard $(OBJ:.o=.d))
