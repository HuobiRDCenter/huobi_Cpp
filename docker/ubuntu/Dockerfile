FROM ubuntu:18.04

USER root

ENV DEBIAN_FRONTEND noninteractive
ENV DEBCONF_NOWARNINGS yes

#更新
RUN apt-get update && apt-get install --assume-yes apt-utils

#安装程序依赖的包
RUN apt-get install -yq --no-install-recommends build-essential
RUN apt-get install -yq --no-install-recommends pkg-config

#权限
RUN apt-get install -yq --no-install-recommends sudo

#加密
RUN apt-get install -yq --no-install-recommends openssl
RUN apt-get install -yq --no-install-recommends libssl-dev
RUN apt-get install -yq --no-install-recommends ca-certificates

#下载
RUN apt-get install -yq --no-install-recommends curl
RUN apt-get install -yq --no-install-recommends libcurl4-openssl-dev

#编译
RUN apt-get install -yq --no-install-recommends git
RUN apt-get install -yq --no-install-recommends cmake
RUN apt-get install -yq --no-install-recommends clang

#网络
RUN apt-get install -yq --no-install-recommends iputils-ping
RUN apt-get install -yq --no-install-recommends net-tools

#编辑器
RUN apt-get install -yq --no-install-recommends vim

#压缩
RUN apt-get install -yq --no-install-recommends zlib1g-dev

#中文支持
RUN apt-get install -yq --no-install-recommends locales
RUN apt-get install -yq --no-install-recommends language-pack-zh-hans

#升级
RUN apt-get -y upgrade

#支持中文
RUN echo "zh_CN.UTF-8 UTF-8" > /etc/locale.gen && locale-gen

# Configure environment
ENV SHELL /bin/bash
ENV NB_USER jovyan
ENV NB_UID 1000
ENV LANG zh_CN.UTF-8
ENV LANGUAGE zh_CN.UTF-8
ENV LC_ALL zh_CN.UTF-8
ENV USER_HOME /home/$NB_USER
ENV WORK_DIR $USER_HOME/work
ENV TMP_DIR $USER_HOME/tmp


# Create jovyan user with UID=1000 and in the 'users' group
#用户名 jovyan  密码:123456
RUN useradd -p `openssl passwd 123456` -m -s $SHELL -u $NB_UID -G sudo $NB_USER
#免密
RUN echo "jovyan  ALL=(ALL:ALL) NOPASSWD: ALL" >> /etc/sudoers

#解析主机名
RUN echo "127.0.1.1 $(hostname)" >> /etc/hosts

USER $NB_USER

# Setup jovyan home directory
RUN mkdir $WORK_DIR && mkdir $USER_HOME/.local

#安装libdecnumber
RUN cd $USER_HOME && git clone https://github.com/huobiapi/libdecnumber.git && cd libdecnumber && mkdir build && cd build && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_COMPILER_TYPE=CLANG && make && sudo make install && sudo rm -rf $USER_HOME/libdecnumber

#安装libwebsockets v3.1.0:
#参考: https://libwebsockets.org/
RUN cd $USER_HOME && git clone https://github.com/warmcat/libwebsockets.git && cd libwebsockets && git reset --hard 89eedcaa94e1c8a97ea3af10642fd224bcea068f  && mkdir build && cd build && cmake .. && make && sudo make install && sudo rm -rf $USER_HOME/libwebsockets


#刷新库文件
RUN sudo ldconfig

WORKDIR $WORK_DIR

VOLUME ["/home/jovyan/work"]

#保持运行状态
ADD idle.sh $TMP_DIR/idle.sh
CMD [ "/bin/bash", "/home/jovyan/tmp/idle.sh" ]


