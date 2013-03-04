#!/usr/bin/make -f

CC = gcc
CFLAGS=-g -W -Wall

SRC = src
BUILD = build
EXEC = $(BUILD)/dcliwrap
TEST = $(BUILD)/runtests

_OBJS = \
	string_utils.o \
	service.o \
	conf.o \
	arg.o \
	argparse.o \
	main.o

OBJS = $(patsubst %,$(BUILD)/%,$(_OBJS))

_TSTS = \
	string_utils.o \
	service.o \
	conf.o \
	arg.o \
	argparse.o \
	test_string_utils.o \
	test_service.o \
	test_conf.o \
	test_arg.o \
	test_argparse.o \
	runtests.o

TSTS = $(patsubst %,$(BUILD)/%,$(_TSTS))

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

$(TEST): $(TSTS)
	$(CC) -lcunit -o $(TEST) $^ $(LDFLAGS)

$(BUILD)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/error.h
	$(CC) -o $@ -c $< $(CFLAGS)

test: $(TEST)
	build/runtests

.PHONY: clean

clean:
	rm -f $(BUILD)/*.o $(EXEC) $(TEST)
