set term gif animate delay 10
set output "C:/Users/nikit/source/repos/ConsoleApplication1/forel.gif"
set size square
set title "FOREL"
unset key
do for [i=0:371] {
plot sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'yellow',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'red',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'green',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'blue',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'yellow',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'yellow',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'yellow',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'yellow',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'yellow',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'yellow',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'yellow',
sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/points/step#%d.txt', i) with points lc rgb 'yellow',
}