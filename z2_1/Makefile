CC = gcc
CFLAGS = -fopenmp
TARGET = z21
all: $(TARGET)
$(TARGET): z2_1.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(TARGET)
.PHONY: all clean
