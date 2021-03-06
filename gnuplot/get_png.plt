###########################################################################################################
# Пример использования: gnuplot -e "clusters=$1;data_file='result.txt';output_file='output.png';radius=0.5" get_png.plt
# Где:
# clusters    - Количество кластеров.
# data_file   - Имя файла входящих данных.
# output_file - Имя картинки (*.png).
# radius      - Радиус точек.
###########################################################################################################


set term png size 800,600
set output output_file
set key outside
set datafile separator ";"
set style fill solid 0.5

plot for [i=1:clusters] data_file using 1:(stringcolumn(3) eq 'cluster'.i? column(2):1/0):(radius) title 'cluster'.i with circles
