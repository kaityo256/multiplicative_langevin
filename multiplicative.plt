set term png
set out "multiplicative.png"

p "multiplicative.dat" pt 6 t ""\
,exp(-x**2/2)/sqrt(2*pi) lw 2.0 lc rgb "black"\
,exp(-x**2/2)*sqrt(1+x**2)/3.4 lw 2.0 lc rgb "red"

