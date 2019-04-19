#!/bin/bash

cd ..
make clean
make
make tests
./build/test1
