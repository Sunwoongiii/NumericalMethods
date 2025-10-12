# Compiler settings
CC = clang
CFLAGS = -O2 -Wall -std=c99 -Wno-unused-variable

# Numerical Recipes source and headers
NR_OBJS = nrutil.o ludcmp.o lubksb.o mprove.o gaussj.o svdcmp.o
NR_HDRS = nr.h nrutil.h

# Main program
OBJS = main.o $(NR_OBJS)
TARGET = solve_linear

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

main.o: main.c $(NR_HDRS)
	$(CC) $(CFLAGS) -c main.c

# Numerical Recipes routines
nrutil.o: nrutil.c nrutil.h nr.h
	$(CC) $(CFLAGS) -c nrutil.c

ludcmp.o: ludcmp.c nr.h nrutil.h
	$(CC) $(CFLAGS) -c ludcmp.c

lubksb.o: lubksb.c nr.h nrutil.h
	$(CC) $(CFLAGS) -c lubksb.c

mprove.o: mprove.c nr.h nrutil.h
	$(CC) $(CFLAGS) -c mprove.c

gaussj.o: gaussj.c nr.h nrutil.h
	$(CC) $(CFLAGS) -c gaussj.c

svdcmp.o: svdcmp.c nr.h nrutil.h
	$(CC) $(CFLAGS) -c svdcmp.c

test: $(TARGET)
	@echo "Creating test data files..."
	@echo "3 3" > lineq1.dat
	@echo "2.0 1.0 1.0" >> lineq1.dat
	@echo "1.0 3.0 2.0" >> lineq1.dat
	@echo "1.0 0.0 0.0" >> lineq1.dat
	@echo "4.0 5.0 6.0" >> lineq1.dat
	@echo "Running test..."
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) lineq*.dat
