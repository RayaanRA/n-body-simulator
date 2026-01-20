CPHYS_LIB = ../cphys/libcphys.a
CPHYS_SRC_DIR = ../cphys/src
CPHYS_INCLUDE_DIR = ../cphys/include
SRC_DIR = src

CC = gcc
CFLAGS = -Wall -O2 -I$(CPHYS_INCLUDE_DIR)
LDFLAGS = $(CPHYS_LIB) -lm

DRIVER_SRC = $(SRC_DIR)/main.c
TARGET = nbody_sim

# Optional Raylib
USE_RAYLIB ?= 0
ifeq ($(USE_RAYLIB),1)
    CFLAGS += -I/usr/local/include
    LDFLAGS += -lraylib -ldl -lGL -lm -lpthread -lX11 -lrt -lXrandr -lXi -lopenal
endif

all: $(TARGET)

$(TARGET): $(DRIVER_SRC)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
