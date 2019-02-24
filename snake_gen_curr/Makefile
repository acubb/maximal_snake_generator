GCC = g++ -g

generator: main.o maxgen.o snake.o
	$(GCC) main.o maxgen.o snake.o -o generator

main.o: main.cc maxgen.h
	$(GCC) -c main.cc

maxgen.o: maxgen.cc maxgen.h snake.h
	$(GCC) -c maxgen.cc

snake.o: snake.cc snake.h
	$(GCC) -c snake.cc
