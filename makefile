CC=gcc  #compiler
TARGET=Sim #DO NOT CHANGE -- See project instructions
 
all:
	$(CC) main.c ParseInput.c m1.c -lm -o $(TARGET)
 
clean:
	rm $(TARGET)