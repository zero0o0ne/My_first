set term gif animate delay 20
set output "C:/Users/nikit/source/repos/ConsoleApplication1/ierarh.gif"
set size square
unset key
do for [i=0:37100] {
plot sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'gray' , sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/edges/step#%d.txt', i) with lines lc rgb 'blue'
}