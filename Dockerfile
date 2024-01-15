ARG ROS_DISTRO=humble

# FROM luxonis/depthai-ros:v2.8.1-humble 

FROM ros:${ROS_DISTRO}-ros-base
# FROM luxonis/depthai-ros:foxy-latest
# FROM dustynv/ros:foxy-ros-base-l4t-r32.7.1
# FROM dustynv/ros:humble-pytorch-l4t-r32.7.1

ARG BUILD_TYPE="RelWithDebInfo"
ARG SIM=0
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get -y install --no-install-recommends \
    zsh \
    software-properties-common \
    libusb-1.0-0-dev \
    python3-colcon-common-extensions \
    python3-rosdep \
    build-essential \
    gpiod \
    ros-${ROS_DISTRO}-pcl-ros \
    # libasound2-dev \
    # ros-foxy-cv-bridge \ 
    # ros-foxy-image-transport \
    # ros-foxy-image-transport-plugins \
    # ros-foxy-rmw-cyclonedds-cpp \
    gstreamer1.0-plugins-bad \
    alsa-utils \
    mpg123 \
    libmpg123-dev \
    # ros-foxy-rtabmap-slam \ 
    unzip \
    ffmpeg \
    # ros-foxy-image-proc \
    git \
    wget \
    htop \
    python3-pip 

# RUN pip3 install aqtinstall -y
# RUN aqt install-qt linux desktop 5.12.2 -y

