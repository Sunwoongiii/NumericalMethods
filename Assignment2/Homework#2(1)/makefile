# Compiler and flags
CC      := clang
CFLAGS  := -O2 -Wall -Wextra -std=c11
LDFLAGS :=
LDLIBS  := -lm

# Project name
TARGET  := j0_roots

# Source files
SRCS := \
    main.c \
    rtbis.c \
    rtflsp.c \
    rtsec.c \
    rtnewt.c \
    rtsafe.c \
    zbrak.c \
    bessj0.c \
    bessj1.c \
    nrerror.c 

# Object files
OBJS := $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Pattern rule for compilation
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Convenience targets
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

# Dependencies (optional; you can generate with gcc -MM)
# If you want auto-deps, uncomment below:
# CFLAGS += -MMD -MP
# -include $(SRCS:.c=.d)
