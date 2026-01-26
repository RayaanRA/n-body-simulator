CPHYS_LIB = ../cphys/libcphys.a
CPHYS_INCLUDE_DIR = ../cphys/include
SRC_DIR = src
INCLUDE_DIR = include

CC = gcc
CFLAGS = -Wall -I$(CPHYS_INCLUDE_DIR) -I$(INCLUDE_DIR)
LDFLAGS = $(CPHYS_LIB) -lm

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/sim.c $(SRC_DIR)/log.c
TARGET = nbody_sim

USE_RAYLIB ?= 0
ifeq ($(USE_RAYLIB),1)
    CFLAGS += -DUSE_RAYLIB -I/usr/local/include
    SRC += $(SRC_DIR)/render_raylib.c
    LDFLAGS += -lraylib -ldl -lGL -lpthread -lX11 -lrt -lXrandr -lXi -lopenal
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
