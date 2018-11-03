cat ../data/data_sky.txt | kkmeans $1 > result.txt
gnuplot -e "clusters=$1;data_file='result.txt';output_file='output_sky.png';radius=-1" get_png.plt
rm result.txt