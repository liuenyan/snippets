ALL=getifaddrs clock_time
CC = gcc
CFLAGS = -g -Wall

all:$(ALL) 

getifaddrs:
	$(CC) $(CFLAGS) getifaddrs.c -o getifaddrs

clock_time:
	$(CC) $(CFLAGS) clock_time.c -o clock_time

.PHONY:clean
clean:
	$(RM) $(ALL)

