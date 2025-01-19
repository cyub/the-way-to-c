CC = gcc

all: read_allopt read_opt getopt getopt_long getopt_long_customopt

.PHONY: all clean read_allopt read_opt getopt getopt_long getopt_long_customopt

read_allopt: read_allopt.c
	$(CC) -o $@ $<

read_opt: read_opt.c
	$(CC) -o $@ $<

getopt: getopt.c
	$(CC) -o $@ $<

getopt_long: getopt_long.c
	$(CC) -o $@ $< 

getopt_long_customopt: getopt_long_customopt.c
	$(CC) -o $@ $< 

clean:
	rm -f read_allopt read_opt getopt getopt_long getopt_long_customopt