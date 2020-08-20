#
# Ubuntu Dockerfile
#
# https://github.com/dockerfile/ubuntu
#

# Pull base image.
FROM ubuntu:18.04

# Install.
RUN \
  sed -i 's/# \(.*multiverse$\)/\1/g' /etc/apt/sources.list && \
  apt-get update && \
  apt-get -y upgrade && \
  apt-get install -y build-essential && \
  apt-get install -y curl git vim wget cmake && \
  apt-get install -y libssl-dev libcurl4-openssl-dev zlib1g-dev libcpprest-dev && \
  rm -rf /var/lib/apt/lists/*

# Set environment variables.
ENV HOME /root

# Define working directory.
WORKDIR /root

RUN \
  git clone https://github.com/huobiapi/huobi_Cpp.git && \
  cd huobi_Cpp && \
  mkdir build && \
  cd build && \
  cmake .. -DCMAKE_PREFIX_PATH=/opt/cpprest-2.10.16/lib64/cmake/ && \
  make && \
  make install

WORKDIR /root

RUN \
  cd huobi_Cpp/demo/reference && \
  mkdir build && \
  cd build && \
  cmake .. -DCMAKE_PREFIX_PATH=/opt/cpprest-2.10.16/lib64/cmake/ -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake && \
  make

# Define default command.
CMD ["bash"]
