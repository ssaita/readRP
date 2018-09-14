#set terminal png
#set output "test.png"
set xdata time
set timefmt "%Y/%m/%d %H:%M:%S"
set format x "%H:%M:%S"
# set yrange [32440:33095]

set multiplot layout 3,1
plot "TEW_20180901_0001.txt" using 1:3 with lines
plot "TEW_20180901_0001.txt" using 1:4 with lines
plot "TEW_20180901_0001.txt" using 1:5 with lines
unset multiplot
if (exist("FRAG") == 0) \
     pause -1 "Click OK to make EPS file";\
     set out "multiplot.eps";\
     set term post eps color enhanced "Arial,12";\
     FRAG = 1; reread

undefine FRAG
set out
set term pop