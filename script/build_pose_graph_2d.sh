#!/bin/bash
to_abs_path() {
    local RELATIVE_PATH=$(echo "`dirname $0`"/$@)
    echo $(realpath $RELATIVE_PATH)
}

PROJECT_ABS_PATH=$(to_abs_path ../)

${PROJECT_ABS_PATH}/build/example/slam/pose_graph_2d/pose_graph_2d --input ${PROJECT_ABS_PATH}/example/slam/dataset/2d/input_M3500_g2o.g2o
