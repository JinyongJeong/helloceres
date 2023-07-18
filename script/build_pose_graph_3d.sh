#!/bin/bash
to_abs_path() {
    local RELATIVE_PATH=$(echo "`dirname $0`"/$@)
    echo $(realpath $RELATIVE_PATH)
}

PROJECT_ABS_PATH=$(to_abs_path ../)

${PROJECT_ABS_PATH}/build/example/slam/pose_graph_3d/pose_graph_3d --input ${PROJECT_ABS_PATH}/example/slam/dataset/3d/sphere_bignoise_vertex3.g2o
