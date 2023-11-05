CC = gcc
CFLAGS = -fopenmp
TARGET = z23
all: $(TARGET)
$(TARGET): z2_3.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(TARGET)
.PHONY: all clean
