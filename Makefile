# -*- Makefile -*-

CC        := gcc
CCFLAGS   := -std=c99 -Wall -Wextra -Wfatal-errors -pthread
TARGET    := game-of-life
BUILD_DIR := build/
SRCDIRS   := $(shell find src -type d)
SOURCES   := $(foreach D,$(SRCDIRS), $(wildcard $(D)/*.c))
OBJS      := $(addprefix $(BUILD_DIR),$(SOURCES:.c=.o))
DEPS      := $(OBJS:.o=.d)

.PHONY: all bear clean mem-check run

all: $(TARGET)

bear:
	$(MAKE) clean
	bear -- $(MAKE)

build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c -MMD -o $@ $<

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) -o $(TARGET) $^ $(LDLIBS)

-include $(DEPS)

run: $(TARGET)
	./$(TARGET)
	@rm $(TARGET)

mem-check: $(TARGET)
	valgrind ./$(TARGET)
	@rm $(TARGET)

clean:
	@rm -rvf $(TARGET) $(OBJS) $(DEPS)

