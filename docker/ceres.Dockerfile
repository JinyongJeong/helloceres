From ubuntu:22.04

RUN apt update && \
    apt install -y cmake build-essential vim nano git clang-format-11

RUN apt install -y libgoogle-glog-dev libgflags-dev libatlas-base-dev libeigen3-dev libsuitesparse-dev wget python3-pip python3-tk
RUN pip3 install matplotlib
RUN cd /tmp && \
	wget http://ceres-solver.org/ceres-solver-2.1.0.tar.gz &&\
	tar zxf ceres-solver-2.1.0.tar.gz && \
	mkdir ceres-bin && \
	cd ceres-bin && \
	cmake ../ceres-solver-2.1.0 && \
	make -j3 && \
	make test && \
	make install
