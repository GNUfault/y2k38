CC      = gcc
SRC     = y2k38.c
BIN     = y2k38
OPT     = s
GDB     = 0
MARCH   = i386
MTUNE   = $(MARCH)
STD     = c99
FLAGS   = -Wall -Wextra -pedantic -pedantic-errors
LDFLAGS = -static
LDLIBS  = -lncurses
CFLAGS  = -O$(OPT) -g$(GDB) -march=$(MARCH) -mtune=$(MTUNE) -std=$(STD) $(FLAGS) $(LDFLAGS) $(LDLIBS)
SUDO    = sudo
DEST    = /usr/local/bin
INSTALL = $(DEST)/$(BIN)

all: compile strip

compile:
  $(CC) $(SRC) -o $(BIN) $(CFLAGS)

strip:
  objcopy --strip-all $(BIN)

install:
  $(SUDO) mkdir -p $(DEST)
  $(SUDO) install -m 755 $(BIN) $(INSTALL)

remove:
  sudo rm -f $(INSTALL)

clean:
  rm -f $(BIN)
