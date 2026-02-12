# ====== Настройки компиляции ======
CC       = gcc
CFLAGS   = -fPIC -Wall -Wextra -O2 -MMD -MP
LDFLAGS  = -L$(BUILD_DIR)
LDLIBS   = -lstationmapper -lm

# ====== Директории ======
BUILD_DIR   = build
SRC_DIR     = src
EXAMPLE_DIR = example_src

# ====== Файлы проекта ======
LIB_SRC = $(SRC_DIR)/stationmapper.c
LIB_OBJ = $(BUILD_DIR)/stationmapper.o
LIB_SO  = $(BUILD_DIR)/libstationmapper.so

EXAMPLE_SRC = $(EXAMPLE_DIR)/example.c
EXAMPLE_BIN = $(BUILD_DIR)/example

# ====== Цели по умолчанию ======
.PHONY: all clean run

all: $(LIB_SO) $(EXAMPLE_BIN)

# ====== Создание директории build ======
$(BUILD_DIR):
	mkdir -p $@

# ====== Компиляция объектного файла ======
$(LIB_OBJ): $(LIB_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ====== Сборка разделяемой библиотеки ======
$(LIB_SO): $(LIB_OBJ)
	$(CC) -shared $^ -o $@

# ====== Сборка исполняемого файла ======
$(EXAMPLE_BIN): $(EXAMPLE_SRC) $(LIB_SO) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -Wl,-rpath,$(abspath $(BUILD_DIR)) -o $@ $< $(LDLIBS)

# ====== Автоматическое подключение зависимостей ======
-include $(BUILD_DIR)/*.d

# ====== Очистка ======
clean:
	rm -rf $(BUILD_DIR)

# ====== Запуск примера (после сборки) ======
run: $(EXAMPLE_BIN)
	./$(EXAMPLE_BIN) ./data/map_1.bmp ./data/map_1.csv ./data/stations_1.csv