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

## 2. Docker compose 설치

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

pose graph tutorial 의 경우 실행, visualization 에 대한 script를 제공한다. `show_pose_graph_2d.sh` 스크립트는 최적화 결과를 GUI를 통해 보여준다. docker 안에서 GUI 관련된 컴포넌트를 실행시키기 위해서는 다음의 명령어를 host에서 실행해줘야 한다. 

```
xhost +
```

이제 아래 script를 통해 실행할 수 있다. (2D graph optimization, 3D graph Optimization)


```
./script/run_pose_graph_2d.sh   // Run 2d graph optimize with data & export result
./script/visualize_pose_graph_2d_result.sh  // Show 2d graph optimization result with GUI 
./script/run_pose_graph_3d.sh   // Run 3d graph optimize with data & export result
./script/visualize_pose_graph_3d_result.sh  // Show 3D graph optimization result with GUI
```

---


# Tutorial Contents

```
1_helloworld.cc : 가장 기본적인 1차식 최적화
2_add_residual_1.cc : Residual 을 추가하는 방법 1
3_add_residual_2.cpp : Residual 을 추가하는 방법 2
4_multivariate.cc : 다변수로 입력과 Residual 추가하는 방법
5_analytic_diff.cc : Jacobian 을 추가하여 Analytic 하게 최적화 하는 방법 1 
6_analytic_diff2.cc :Jacobian 을 추가하여 Analytic 하게 최적화 하는 방법 2
7_analytic_diff3.cc : Jacobian 을 추가하여 Analytic 하게 최적화 하는 방법 3
8_analytic_and_autodiff.cc : Analytic 방법과 Numeric 하게 최적화 하는 방법 비교
9_curve_fitting.cc : Exponential Curve fitting
10_curve_fitting2.cc : 2차식 Curve Fitting
11_pose_2d_fixed_a.cc : Residual 을 이용한 parameter 고정하는 방법
12_pose_2d_fixed_b.cc : 함수를 이용한 parameter 고정하는 방법
13_pose_graph_2d : 2D graph Optimization
14_pose_graph_3d : 3D graph Optimization
```