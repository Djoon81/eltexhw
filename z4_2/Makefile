CC = gcc
CFLAGS = -fopenmp
TARGET = z42
all: $(TARGET)
$(TARGET): z4_2.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(TARGET)
.PHONY: all clean
