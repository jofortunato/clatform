CC=gcc
CFLAGS=-g -Wall -std=c99 -pedantic
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := $(INC_FLAGS) -MMD -MP

LIBFLAGS= -lncurses

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS) -o $@ $(LIBFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LIBFLAGS)

.PHONY: clean
clean:
	$(RM) bin/* $(OBJ)/*

-include $(DEPS)
