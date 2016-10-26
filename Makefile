all: getifaddrs

CC = gcc
CFLAGS = -g -Wall

getifaddrs:
	$(CC) $(CFLAGS) getifaddrs.c -o getifaddrs

.PHONY:clean
clean:
	$(RM) getifaddrs

