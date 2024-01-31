CC = gcc
OPT = -O1
CFLAGS = -Wall -Wextra -Wshadow -std=c99 $(OPT) -I include/ -I include/lua/

ifeq ($(OS), Windows_NT)
	MKDIR = @mkdir
	RM = @rmdir /s /q
	LIBS = -L lib/ -lglfw3_win -lgdi32 -lwinmm
	BIN = out.exe
else # Linux
	MKDIR = @mkdir -p
	RM = @rm -r
	LIBS = -L lib/ -lglfw3 -lGL -ldl -lm -lX11 -lXi -lXcursor
	BIN = out
endif


BIN_DIR = bin
OBJ_DIR = obj

LUA_OBJS = lapi.o lcode.o lctype.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o \
    lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o \
    ltm.o lundump.o lvm.o lzio.o ltests.o lauxlib.o \
	lbaselib.o ldblib.o liolib.o lmathlib.o loslib.o ltablib.o lstrlib.o \
    lutf8lib.o loadlib.o lcorolib.o linit.o

OBJS = $(LUA_OBJS) gl.o main.o engine.o window.o

all: create_dir $(BIN_DIR)/$(BIN)

create_dir:
	$(MKDIR) bin
	$(MKDIR) obj

# Create executable.
$(BIN_DIR)/$(BIN): $(addprefix $(OBJ_DIR)/,$(OBJS))
	@$(CC) -o $@ $^ $(LIBS)

# Lua
$(addprefix $(OBJ_DIR),/%.o):lib/lua/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Create object files.
$(addprefix $(OBJ_DIR),/%.o):src/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) bin
	$(RM) obj

