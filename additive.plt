set term png
set out "additive.png"

p "additive.dat" pt 6\
, exp(-x**2/2)/sqrt(2*pi) lw 2.0 lc rgb "black" t "Ito, Stratonovich"
