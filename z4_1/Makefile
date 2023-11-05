CC = gcc
CFLAGS = -fopenmp
TARGET = z41
all: $(TARGET)
$(TARGET): z4_1.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(TARGET)
.PHONY: all clean
