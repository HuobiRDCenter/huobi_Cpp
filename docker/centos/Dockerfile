FROM centos:7.6.1810

USER root

#关闭SELinux
RUN echo "SELINUX=disabled" > /etc/selinux/config

#更新
RUN yum update -y
RUN yum group install 'Development Tools' -y
RUN yum install -y  centos-release-scl-rh centos-release-scl scl-utils-build scl-utils
RUN yum check-update -y

#使用redhat源
RUN yum install -y wget
RUN wget http://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
RUN rpm -Uvh epel-release-latest-7.noarch.rpm
RUN rm epel-release-latest-7.noarch.rpm
RUN yum update -y


#权限  执行 sudo su 切换到root
RUN yum install -y  sudo

#编译
RUN yum install -y  git
RUN yum install -y  cmake
RUN yum install -y  libtool
RUN yum install -y  perl-core

#压缩
RUN yum install -y  zlib-devel

#下载
RUN yum install -y  libcurl-devel

#网络
RUN yum install -y  net-tools

#编辑器
RUN yum install -y  vim

#加密
RUN yum install -y openssl-devel

#安装libwebsockets v3.1.0
RUN yum install -y libwebsockets-devel

#单元测试
RUN yum install -y gtest-devel gmock-devel

#升级
RUN yum -y  upgrade

#gcc 最低4.9.2 最高7.3.1 此处使用7.3.1
RUN yum install -y devtoolset-7-toolchain

# Configure environment
ENV SHELL /bin/bash
ENV NB_USER jovyan
ENV NB_UID 1000
ENV LANG zh_CN.UTF-8
ENV LANGUAGE zh_CN.UTF-8
ENV USER_HOME /home/$NB_USER
ENV WORK_DIR $USER_HOME/work
ENV TMP_DIR $USER_HOME/tmp


# Create jovyan user with UID=1000 and in the 'users' group
#用户名 jovyan  密码:123456
RUN useradd -p `openssl passwd 123456` -m -s $SHELL -u $NB_UID -G wheel $NB_USER
#免密
RUN echo "jovyan  ALL=(ALL:ALL) NOPASSWD: ALL" >> /etc/sudoers

#解析主机名
RUN echo "127.0.1.1 $(hostname)" >> /etc/hosts

USER $NB_USER

#安装libdecnumber
RUN source /opt/rh/devtoolset-7/enable && cd $USER_HOME && git clone https://github.com/huobiapi/libdecnumber.git && cd libdecnumber && mkdir build && cd build && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release && make && sudo make install && sudo rm -rf $USER_HOME/libdecnumber

#刷新库文件
RUN sudo ldconfig

# Setup jovyan home directory
RUN mkdir $WORK_DIR && mkdir $USER_HOME/.local
RUN echo "source /opt/rh/devtoolset-7/enable" >> $USER_HOME/.bashrc


WORKDIR $WORK_DIR
VOLUME ["/home/jovyan/work"]

#保持运行状态
ADD idle.sh $WORK_DIR/idle.sh
CMD [ "/bin/bash", "/home/jovyan/work/idle.sh" ]


