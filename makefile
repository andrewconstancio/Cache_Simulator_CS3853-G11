CC=gcc  #compiler
TARGET=Sim #DO NOT CHANGE -- See project instructions
 
all:
	$(CC) main.c ParseInput.c m1.c ParseHex.c -lm -o $(TARGET)
 
clean:
	rm $(TARGET)
