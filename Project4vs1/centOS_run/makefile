Makefile:

all: clean controller compute run

controller: controller.c
	g++ controller.c -o controller -pthread -std=c++0x

compute: compute_processes.c
	g++ compute_processes.c -o compute -std=c++0x

run: controller
	./controller

clean:
	rm -f controller
	rm -f compute_processes
