#!/usr/bin/make -f

CC = gcc
CFLAGS=-g -W -Wall

SRC = src
BUILD = build
EXEC = $(BUILD)/ndcwrap
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

test: $(TEST) $(EXEC)
	$(TEST)
	DCLIWRAP_CONFIG=test/sample.conf DCLIWRAP_DEBUG=1 $(EXEC) a b DYN:SRV12:WARN:5|grep "a b 1"
	DCLIWRAP_CONFIG=test/sample.conf DCLIWRAP_DEBUG=1 $(EXEC) a b DYN:SRV12:CRIT:5|grep "a b 2"
	DCLIWRAP_CONFIG=test/sample.conf DCLIWRAP_DEBUG=1 $(EXEC) a b DYN:SRV13:CRIT:5|grep "a b 5"
	DCLIWRAP_CONFIG=test/sample.conf $(EXEC) test/printarg a b DYN:SRV12:CRIT:5|grep "a b 2"
	echo "All tests successfully passed."

.PHONY: clean

clean:
	rm -f $(BUILD)/*.o $(EXEC) $(TEST)
