.default: all

all: cpuscheduler

cpuscheduler:  main.o Process.o Queue.o Scheduler.o
	g++ -Wall -Werror -std=c++11 -O -o $@ $^

clean:
	rm -rf cpuscheduler *.o *.dSYM