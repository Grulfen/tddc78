#!/bin/bash

echo "1 process" >> result/thres/result.txt
python3 get_average_time.py result/thres/batch_thres_1.txt >> result/thres/result.txt
echo "2 processes" >> result/thres/result.txt
python3 get_average_time.py result/thres/batch_thres_2.txt >> result/thres/result.txt
echo "3 processes" >> result/thres/result.txt
python3 get_average_time.py result/thres/batch_thres_3.txt >> result/thres/result.txt
echo "4 processes" >> result/thres/result.txt
python3 get_average_time.py result/thres/batch_thres_4.txt >> result/thres/result.txt
echo "5 processes" >> result/thres/result.txt
python3 get_average_time.py result/thres/batch_thres_5.txt >> result/thres/result.txt
echo "8 processes" >> result/thres/result.txt
python3 get_average_time.py result/thres/batch_thres_8.txt >> result/thres/result.txt
echo "10 processes" >> result/thres/result.txt
python3 get_average_time.py result/thres/batch_thres_10.txt >> result/thres/result.txt
echo "13 processes" >> result/thres/result.txt
python3 get_average_time.py result/thres/batch_thres_13.txt >> result/thres/result.txt
echo "16 processes" >> result/thres/result.txt
python3 get_average_time.py result/thres/batch_thres_16.txt >> result/thres/result.txt
