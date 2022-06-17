#!/bin/bash

rm ES.txt

echo -e "\nGKD-b_1_n25_m2.txt" >> ES.txt
../bin/mainES < ../data/GKD-b_1_n25_m2.txt >> ES.txt

echo -e "\nGKD-b_2_n25_m2.txt" >> ES.txt
../bin/mainES < ../data/GKD-b_2_n25_m2.txt >> ES.txt

echo -e "\nGKD-b_3_n25_m2.txt" >> ES.txt
../bin/mainES < ../data/GKD-b_3_n25_m2.txt >> ES.txt

echo -e "\nGKD-b_4_n25_m2.txt" >> ES.txt
../bin/mainES < ../data/GKD-b_4_n25_m2.txt >> ES.txt

echo -e "\nGKD-b_5_n25_m2.txt" >> ES.txt
../bin/mainES < ../data/GKD-b_5_n25_m2.txt >> ES.txt


for i in {6..50}
do
	#echo "Ejecutando main con $i"
	echo -e "\n"GKD-b_$i.txt >> ES.txt
	../bin/mainES < ../data/GKD-b_$i*.txt >> ES.txt

done
