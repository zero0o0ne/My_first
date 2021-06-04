set term gif animate delay 10
set output "C:/Users/nikit/source/repos/ConsoleApplication1/K_cores.gif"
set size square
set title "K cores"
unset key
do for [i=1:300] {
plot sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cluster_1_step#%d.txt', i) with points lc rgb 'purple', sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cluster_2_step#%d.txt', i) with points lc rgb 'yellow', sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cluster_3_step#%d.txt', i) with points lc rgb 'green', sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cluster_4_step#%d.txt', i) with points lc rgb 'grey',sprintf('C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cores_step#%d.txt', i) with points lc rgb 'black'
}