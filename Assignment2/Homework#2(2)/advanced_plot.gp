# 고급 그래프 생성 스크립트
set terminal pngcairo enhanced font "Arial,12" size 1400,1000
set output 'advanced_comparison.png'

# 색상 설정
set style line 1 lc rgb '#1f77b4' lt 1 lw 2 pt 7 ps 1.5
set style line 2 lc rgb '#ff7f0e' lt 1 lw 2 pt 5 ps 1.5  
set style line 3 lc rgb '#2ca02c' lt 1 lw 2 pt 9 ps 1.5
set style line 4 lc rgb '#d62728' lt 1 lw 2 pt 11 ps 1.5
set style line 5 lc rgb '#9467bd' lt 1 lw 2 pt 13 ps 1.5
set style line 6 lc rgb '#8c564b' lt 1 lw 2 pt 15 ps 1.5

set multiplot layout 2,2 margins 0.1,0.95,0.1,0.95 spacing 0.15,0.15

# 1. 수렴 속도 비교 (반복횟수)
set title "수렴 속도 비교 (평균 반복횟수)" font "Arial,14"
set xlabel "수치해법" font "Arial,12"
set ylabel "평균 반복횟수" font "Arial,12"
set style data histograms
set style histogram clustered gap 1
set style fill solid 0.8 border -1
set boxwidth 0.8
set xtics rotate by -20
set grid y
plot 'method_stats.dat' using 2:xtic(1) title "반복횟수" ls 1

# 2. 함수 호출 횟수 비교  
set title "효율성 비교 (평균 함수 호출 횟수)" font "Arial,14"
set ylabel "평균 함수 호출 횟수" font "Arial,12"
plot 'method_stats.dat' using 3:xtic(1) title "함수 호출" ls 2

# 3. 정확도 비교
set title "정확도 비교 (평균 오차)" font "Arial,14"
set ylabel "평균 절대 오차" font "Arial,12"
set logscale y
set format y "10^{%T}"
plot 'method_stats.dat' using 5:xtic(1) title "절대 오차" ls 4

# 4. 종합 성능 지수
unset logscale y
set title "종합 성능 평가" font "Arial,14"
set ylabel "성능 지수 (낮을수록 좋음)" font "Arial,12"
# 성능 지수 = 정규화된(반복횟수 + 함수호출횟수 + 오차*1e6)
plot 'performance_index.dat' using 2:xtic(1) title "성능 지수" ls 3

unset multiplot

# 개별 그래프들도 생성
set output 'convergence_analysis.png'
set terminal pngcairo enhanced font "Arial,14" size 1000,600
unset multiplot

set title "베셀 함수 J_0(x) 근 찾기 - 수렴 특성 비교" font "Arial,16"
set xlabel "수치해법" font "Arial,14"
set ylabel "평균 반복횟수" font "Arial,14"
set style data histograms
set style histogram clustered gap 2
set style fill solid 0.7 border -1
set boxwidth 0.8
set xtics rotate by -15 font "Arial,12"
set ytics font "Arial,12"
set grid y alpha 0.3

# 범례 설정
set key top right font "Arial,12"

# 히스토그램 색상 지정
set palette defined (1 '#1f77b4', 2 '#ff7f0e', 3 '#2ca02c', 4 '#d62728', 5 '#9467bd', 6 '#8c564b')
set style histogram clustered
plot 'method_stats.dat' using 2:xtic(1) title "평균 반복횟수" lc rgb '#1f77b4'
