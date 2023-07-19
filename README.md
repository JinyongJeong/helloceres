# Hello Ceres!


Original Repo: https://github.com/LimHyungTae/helloceres
Original author: Hyungtae Lim (shapelim@kaist.ac.kr)
Updated author: Jinyong Jeong (jjy0923@gmail.com)

---

본 Tutorial 은 Docker를 사용하여 코드를 빌드하는 방식으로 진행한다.


# Installation

## 1. Docker 설치

각자 환경에 맞는 Docker를 설치한다. (참고: https://www.leafcats.com/153)

```
sudo wget -qO- http://get.docker.com/ | sh
```

## 2. Docker compose 설치dd

```
sudo apt-get install -y --no-install-recommends curl python3-pip nano python3-dev
sudo -H pip3 install --upgrade --ignore-installed pip setuptools
sudo pip3 install docker-compose
```

## 3. Docker compose 시작

```
docker-compose -f docker/ceres_docker_compose.yml up -d // Docker 시작
docker-compose -f docker/ceres_docker_compose.yml down  // Docker 종료
```

만약 docker image가 빌드되어 있지 않다면, 빌드 프로세스가 시작되고 완료되면 자동으로 docker가 시작된다.

## 4. Docker 에 접근

```
docker exec -it ceres_dev /bin/bash
```

## 5. Build code

```
cd /helloceres
mkdir build
cd build
cmake ..
make all -j8
```

## 6. Run code

```
./1_helloworld
```

pose graph tutorial 의 경우 실행, visualization 에 대한 script를 제공한다. 

```
./script/run_pose_graph_2d.sh
./script/show_pose_graph_2d.sh
```

---


# Tutorial Contents

1_hellowworld.cc
2_add_residual_1.cc
3_add_residual_2.cpp
4_multivariate.cc
5_analytic_diff.cc
6_analytic_diff2.cc
7_analytic_diff3.cc
8_analytic_and_autodiff.cc
9_curve_fitting.cc
10_curve_fitting2.cc
11_pose_2d_fixed_a.cc
12_pose_2d_fixed_b.cc
13_pose_graph_2d
14_pose_graph_3d