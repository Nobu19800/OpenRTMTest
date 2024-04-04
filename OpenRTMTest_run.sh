#!/usr/bin/env bash

max_count=100
conf=configOpenRTM.txt
recv_port=2809
recv_host=127.0.0.1
recv_name=OpenRTMTestIn0
server_sleep_time=5000000000
wait_time=1000000000

runClient() {
    output_file_out=ret_openrtm_${max_count}_${data_size}_${rate}.txt
    ./OpenRTMTestOut ${conf} --max_count=${max_count} --data_size=${data_size} --rate=${rate} --recv_port=${recv_port} --recv_host=${recv_host} --recv_name=${recv_name}  --server_sleep_time=${server_sleep_time} --server_sleep_time=${server_sleep_time} --wait_time=${wait_time} --output_file_out=${output_file_out}
}

data_size=60
rate=100000
runClient
sleep 3

data_size=60
rate=1000000
runClient
sleep 3

data_size=60
rate=10000000
runClient
sleep 3

data_size=60
rate=50000000
runClient
sleep 3

data_size=1000
rate=10000000
runClient
sleep 3

data_size=1000
rate=25000000
runClient
sleep 3

data_size=1000
rate=50000000
runClient
sleep 3

data_size=1000
rate=100000000
runClient
sleep 3

data_size=8000
rate=10000000
runClient
sleep 3

data_size=8000
rate=25000000
runClient
sleep 3

data_size=8000
rate=50000000
runClient
sleep 3

data_size=8000
rate=100000000
runClient
sleep 3

data_size=20000
rate=10000000
runClient
sleep 3

data_size=20000
rate=25000000
runClient
sleep 3

data_size=20000
rate=50000000
runClient
sleep 3

data_size=20000
rate=100000000
runClient
sleep 3

data_size=3000000
rate=10000000
runClient
sleep 3

data_size=3000000
rate=25000000
runClient
sleep 3

data_size=3000000
rate=50000000
runClient
sleep 3

data_size=3000000
rate=100000000
runClient
sleep 3

data_size=14000000
rate=10000000
runClient
sleep 3

data_size=14000000
rate=25000000
runClient
sleep 3

data_size=14000000
rate=50000000
runClient
sleep 3

data_size=14000000
rate=100000000
runClient
sleep 3

data_size=512
rate=1000000
runClient
sleep 3

data_size=512
rate=10000000
runClient
sleep 3

data_size=3000
rate=1000000
runClient
sleep 3

data_size=3000
rate=10000000
runClient
sleep 3

