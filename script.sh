#!/bin/bash

rm resultados.txt

echo -e "\nGKD-b_1_n25_m2.txt" >> resultados.txt
bin/main < data/GKD-b_1_n25_m2.txt >> resultados.txt

echo -e "\nGKD-b_2_n25_m2.txt" >> resultados.txt
bin/main < data/GKD-b_2_n25_m2.txt >> resultados.txt

echo -e "\nGKD-b_3_n25_m2.txt" >> resultados.txt
bin/main < data/GKD-b_3_n25_m2.txt >> resultados.txt

echo -e "\nGKD-b_4_n25_m2.txt" >> resultados.txt
bin/main < data/GKD-b_4_n25_m2.txt >> resultados.txt

echo -e "\nGKD-b_5_n25_m2.txt" >> resultados.txt
bin/main < data/GKD-b_5_n25_m2.txt >> resultados.txt


for i in {6..50}
do
	#echo "Ejecutando main con $i"
	echo -e "\n"GKD-b_$i.txt >> resultados.txt
	bin/main < data/GKD-b_$i*.txt >> resultados.txt

done
