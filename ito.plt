set term png
set out "ito.png"

p "ito.dat" pt 6 t ""\
,exp(-x**2/2)/sqrt(2*pi) lw 2.0 lc rgb "black" t "Stratnovich"\
,exp(-x**2/2)/sqrt(1+x**2)/1.98 lw 2.0 lc rgb "red" t "Ito"

