CC ?= cc
BUILD_DIR := build
BIN := $(BUILD_DIR)/geptil-ecs

# Найти все .c в src (включая вложенные диры)
SRC := $(shell find src -name '*.c')

# Преобразовать src/.../file.c -> build/.../file.o
OBJ := $(patsubst src/%, $(BUILD_DIR)/%, $(SRC:.c=.o))

# Флаги компиляции
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -Iinclude

# Флаги для генерации dependency-файлов
DEPFLAGS := -MMD -MP

# Флаги для санитайзеров (используются только если DEBUG=1)
SANITIZERS := -fsanitize=address,undefined

# LDFLAGS для линковщика
LDFLAGS :=

ifeq ($(DEBUG),1)
CFLAGS += -O0 -g -fno-omit-frame-pointer $(SANITIZERS)
LDFLAGS += $(SANITIZERS)
else
CFLAGS += -O2 -march=native
endif

# Включаем DEPFLAGS в CFLAGS чтобы каждый .o имел .d
CFLAGS += $(DEPFLAGS)

.PHONY: all run clean help

all: $(BIN)

# Линковка: используем LDFLAGS (включая санитайзеры, если нужны)
$(BIN): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Правило для сборки объекта (путь сохраняется)
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

# Включаем все автоматически сгенерированные dependency-файлы (.d).
# Используем wildcard, чтобы не выдавать ошибку если .d ещё нет.
-include $(wildcard $(OBJ:.o=.d))
