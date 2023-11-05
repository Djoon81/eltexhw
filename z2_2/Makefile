CC = gcc
CFLAGS = -fopenmp
TARGET = z22
all: $(TARGET)
$(TARGET): z2_2.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(TARGET)
.PHONY: all clean
