vpath %.c ../src

CC=gcc
SGDK?=/sgdk
BIN_DIR=bin
OBJ_DIR=obj
CMOCKA_TAR=third_party/cmocka-1.1.7.tar.xz
CMOCKA_DIR=build/deps/cmocka

ifeq ($(DEBUG),1)
	GDB=gdbserver :2345
else
	GDB=
endif

INCLUDE_DIRS+=-I$(SGDK)/inc/ext
INCLUDE_DIRS+=-I$(SGDK)/inc
INCLUDE_DIRS+=-I$(SGDK)/res
INCLUDE_DIRS+=-I.
INCLUDE_DIRS+=-I../res
INCLUDE_DIRS+=-I../src
INCLUDE_DIRS+=-Imocks
INCLUDE_DIRS+=-I$(CMOCKA_DIR)/include

CFLAGS=$(INCLUDE_DIRS) \
	-DBUILD='"$(BUILD)"' \
	-DUNIT_TESTS \
	-DMEGAWIFI \
	-ggdb \
	-O0 \
	-Wall \
	-std=c11 \
	-Werror \
	-Wextra \
	-Wno-char-subscripts \
	-Wno-unused-parameter \
	-Wno-builtin-declaration-mismatch \
	-Wno-unused-function \
	-Wno-packed-bitfield-compat \
	-fsigned-char


 # list of function signature to mock
MOCKS=
MD_MOCKS=

LDFLAGS=-ggdb -ffreestanding -lcmocka \
	-L$(CMOCKA_DIR)/build/src -Wl,-rpath=$(CMOCKA_DIR)/build/src \
	-fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS+=$(foreach MOCK,$(MD_MOCKS),-Wl,--wrap=$(MOCK))
UNIT_TEST_LDFLAGS=$(LDFLAGS) $(foreach MOCK,$(MOCKS),-Wl,--wrap=$(MOCK))

LAST_FLAGS := bin/last_flags
CHECK_FLAGS := $(LAST_FLAGS)_$(shell echo $(CFLAGS) \
	$(UNIT_TEST_LDFLAGS) | md5sum | awk '{ print $$1 }')

SRC=$(wildcard ../src/*.c ../src/*/*.c)
SRC:=$(filter-out ../src/boot/rom_head.c,$(SRC))
SRC:=$(filter-out ../src/main.c,$(SRC))
COMMON_TEST_SRC=$(wildcard *.c mocks/*.c)
UNIT_TEST_SRC=$(wildcard unit/*.c)

SRC_OBJ=$(patsubst ../src/%.c,obj/%.o,$(SRC))
COMMON_TEST_OBJ=$(patsubst %.c,obj/%.o,$(COMMON_TEST_SRC))
UNIT_TEST_OBJ=$(patsubst %.c,obj/%.o,$(UNIT_TEST_SRC))

UNIT_TESTS_TARGET=$(BIN_DIR)/unit_tests

all: unit
.PHONY: all

unit: $(UNIT_TESTS_TARGET) $(CHECK_FLAGS)
	$(GDB) ./$(UNIT_TESTS_TARGET)
.PHONY: unit

$(OBJ_DIR)/%.o: %.c | $(CMOCKA_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MT "$@ $(basename $@).d" -c $< -o $@

-include $(wildcard $(OBJ_DIR)/*.d) $(wildcard $(OBJ_DIR)/*/*.d)

$(UNIT_TESTS_TARGET): $(SRC_OBJ) $(UNIT_TEST_OBJ) $(COMMON_TEST_OBJ) $(CHECK_FLAGS)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(UNIT_TEST_LDFLAGS)

$(CMOCKA_DIR):
	mkdir -p $@
	tar -xf $(CMOCKA_TAR) -C $@ --strip-components 1 --no-same-owner
	mkdir -p $@/build
	@(cd $@/build && cmake ../ && make -s)

$(LAST_FLAGS)_%:
	-rm $(LAST_FLAGS)_*
	touch $@

clean-target:
	rm -rf $(UNIT_TESTS_TARGET) $(SYSTEM_TESTS_TARGET) $(OBJ_DIR)
.PHONY: clean-target

clean: clean-target
	rm -rf build/
.PHONY: clean
