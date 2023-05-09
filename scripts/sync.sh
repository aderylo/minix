#!/bin/bash

cd "$(dirname "$0")" # set current working directory to the directory of the script
cd ..

diff -rupNEZbB minix_source/usr/ solution/usr/ > ab123456.patch
scp ab123456.patch minix:/
scp -r tests minix:/
