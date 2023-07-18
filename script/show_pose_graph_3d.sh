#!/bin/bash
to_abs_path() {
    local RELATIVE_PATH=$(echo "`dirname $0`"/$@)
    echo $(realpath $RELATIVE_PATH)
}

PROJECT_ABS_PATH=$(to_abs_path ../)

python3 ${PROJECT_ABS_PATH}/example/slam/pose_graph_3d/plot_results.py --optimized_poses ${PROJECT_ABS_PATH}/build/example/slam/pose_graph_3d/poses_optimized.txt --initial_poses ${PROJECT_ABS_PATH}/build/example/slam/pose_graph_3d/poses_original.txt
