set tmargin 1.5
set xtics offset 0,-0.4 font",26"
set ytics font ",26"
set xrange [-1:]
set yrange [0:]   
set boxwidth 0.9 relative
set style data histograms
set key title 'amount of points' font ",32"
plot for [COL=2:4:2] 'C:\Users\nikit\source\repos\ConsoleApplication1\histogram_edges.txt'\
using COL:xticlabels(1) title columnhea