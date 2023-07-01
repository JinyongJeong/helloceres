#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")/.."
set -x

docker build -t ceres_ubuntu:latest -f docker/ceres.Dockerfile .
docker images ceres_ubuntu:latest
