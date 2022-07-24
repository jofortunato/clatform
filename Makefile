CC=gcc
CFLAGS=-I -Wall -ansi -pedantic
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

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@ 

.PHONY: clean
clean:
	$(RM) bin/* $(OBJ)/*

-include $(DEPS)
