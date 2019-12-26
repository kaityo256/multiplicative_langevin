all: a.out

a.out: langevin.cpp
	g++ -O3 -std=c++11 $<

clean:
	rm -f a.out
