#!/bin/bash

rm ILS.txt

echo -e "\nGKD-b_1_n25_m2.txt" >> ILS.txt
../bin/mainILS < ../data/GKD-b_1_n25_m2.txt >> ILS.txt

echo -e "\nGKD-b_2_n25_m2.txt" >> ILS.txt
../bin/mainILS < ../data/GKD-b_2_n25_m2.txt >> ILS.txt

echo -e "\nGKD-b_3_n25_m2.txt" >> ILS.txt
../bin/mainILS < ../data/GKD-b_3_n25_m2.txt >> ILS.txt

echo -e "\nGKD-b_4_n25_m2.txt" >> ILS.txt
../bin/mainILS < ../data/GKD-b_4_n25_m2.txt >> ILS.txt

echo -e "\nGKD-b_5_n25_m2.txt" >> ILS.txt
../bin/mainILS < ../data/GKD-b_5_n25_m2.txt >> ILS.txt


for i in {6..50}
do
	#echo "Ejecutando main con $i"
	echo -e "\n"GKD-b_$i.txt >> ILS.txt
	../bin/mainILS < ../data/GKD-b_$i*.txt >> ILS.txt

done
