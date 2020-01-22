PANDOC_TEXOPT=--highlight-style tango --latex-engine=lualatex -V documentclass=ltjarticle -V geometry:margin=1in -H mytemplate.tex

all: a.out

a.out: langevin.cpp
	g++ -O3 -std=c++11 $<

graph:
	gnuplot additive.plt
	gnuplot ito.plt
	gnuplot stratonovich.plt
	gnuplot twostep.plt
	gnuplot milstein.plt


pdf:
	pandoc README.md -s -o README.pdf $(PANDOC_TEXOPT)

clean:
	rm -f a.out
