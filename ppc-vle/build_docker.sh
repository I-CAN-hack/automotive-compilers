#!/usr/bin/env bash
set -e

docker build -t vle-gcc .
docker run --rm -v $(pwd):/src vle-gcc ./build.sh
