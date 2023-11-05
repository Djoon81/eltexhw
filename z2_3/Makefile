CC = gcc
CFLAGS = -fopenmp
LDFLAGS = -lm
TARGET = z23
all: $(TARGET)
$(TARGET): z2_3.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	rm -f $(TARGET)
.PHONY: all clean
