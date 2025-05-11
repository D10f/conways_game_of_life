# -*- Makefile -*-

CC        := gcc
CCFLAGS   := -std=c99 -Wall -Wextra -Wfatal-errors -pthread
TARGET    := game-of-life
LIBS      := SDL2 m
BUILD_DIR := build/
SRCDIRS   := src/
LDLIBS    := $(addprefix -l,$(LIBS))
SOURCES   := $(foreach D,$(SRCDIRS), $(wildcard $(D)*.c))
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
	valgrind \
		--leak-check=full \
		--track-origins=yes \
		--show-reachable=yes \
		./$(TARGET)
	@rm $(TARGET)

clean:
	@rm -rvf $(TARGET) $(OBJS) $(DEPS)

