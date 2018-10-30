###########################################################################################################
# Пример использования: gnuplot -e "clusters='2';data_file='data.txt';output_file='output.png'" get_png.plt
# Где:
# clusters    - Количество кластеров.
# data_file   - Имя файла входящих данных.
# output_file - Имя картинки (*.png).
###########################################################################################################


set term png
set output output_file
set key outside
set datafile separator ";"

plot for [i=1:clusters] data_file using 1:(stringcolumn(3) eq 'cluster'.i? column(2):1/0) title 'cluster'.i with circles fs solid
