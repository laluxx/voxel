CC = gcc
TARGET = voxel
CFLAGS = -Wall -Wextra -I.
LFLAGS = -lraylib -lm -g
SOURCES = ./*.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LFLAGS) -o $(TARGET)
	@echo "Linking complete!"

.PHONEY: clean
clean:
	@rm -f $(TARGET)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@rm -f $(TARGET)
	@echo "Executable removed!"
