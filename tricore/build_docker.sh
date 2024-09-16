#!/usr/bin/env bash
set -e

docker build -t tricore-gcc .
docker run --rm -v $(pwd):/src tricore-gcc ./build.sh
