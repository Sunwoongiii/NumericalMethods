set terminal png size 1200,800
set output 'comparison_results.png'
set multiplot layout 2,2

set title 'Iterations Comparison'
set xlabel 'Method'
set ylabel 'Average Iterations'
set style data histograms
set style histogram clustered
set style fill solid 0.7
set xtics rotate by -45
plot 'method_stats.dat' using 2:xtic(1) title 'Iterations' linecolor rgb '#1f77b4'

set title 'Function Calls Comparison'
set ylabel 'Average Function Calls'
plot 'method_stats.dat' using 3:xtic(1) title 'Function Calls' linecolor rgb '#ff7f0e'

set title 'Execution Time Comparison'
set ylabel 'Average Time (ms)'
plot 'method_stats.dat' using 4:xtic(1) title 'Time' linecolor rgb '#2ca02c'

set title 'Accuracy Comparison'
set ylabel 'Average Error'
set logscale y
plot 'method_stats.dat' using 5:xtic(1) title 'Error' linecolor rgb '#d62728'

unset multiplot
