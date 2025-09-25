CC = clang
CFLAGS = -O2 -Wall -std=c11
LDFLAGS = -lm

SRC = main.c muller.c nr_wrap.h nrutil.c zbrak.c rtbis.c rtflsp.c rtsec.c rtnewt.c rtsafe.c bessj0.c bessj1.c
OBJ = main.o muller.o nrutil.o zbrak.o rtbis.o rtflsp.o rtsec.o rtnewt.o rtsafe.o bessj0.o bessj1.o
TARGET = find_roots

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

# nr_wrap.h is a header-only wrapper; no .o target needed

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
