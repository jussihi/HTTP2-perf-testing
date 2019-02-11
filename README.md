# HTTP2-perf-testing
Testing of HTTP/2 protocol performance with nghttp2_asio for Aalto university course ELEC-E7320 - Internet Protocols

This repository is about testing the latency improvements of the new HTTP/2 features *server push* and *stream multiplexing*


## Requirements

*gcc (C++14), boost, libnghttp2_asio*

## Usage

Compile with 

`$ make test`

Add some latency, if you want to use the same setup as I did (30ms static +-15ms random with normal distribution), you can use tc;

`# tc qdisc add dev lo root netem delay 30ms 15ms distribution normal`

Run tests by 

`$ tester.sh test-name`

For example to test the multiplexing

`$ tester test-multi`

Generate plots by running

`source("octave-script")`
in GNU octave
