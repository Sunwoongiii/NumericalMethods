CC = clang
CFLAGS = -Wall -Wextra -std=c99 -O2
LDLIBS = -lm
TARGET = bessel_roots
OBJS = main.o bessel.o rootfinding.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

main.o: main.c bessel.h rootfinding.h
	$(CC) -c main.c $(CFLAGS)

bessel.o: bessel.c bessel.h
	$(CC) -c bessel.c $(CFLAGS)

rootfinding.o: rootfinding.c rootfinding.h
	$(CC) -c rootfinding.c $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET) *.csv *.dat *.png

plot: $(TARGET)
	./$(TARGET)
	gnuplot plot_results.gp
	echo "그래프가 comparison_results.png로 저장되었습니다."

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean plot run