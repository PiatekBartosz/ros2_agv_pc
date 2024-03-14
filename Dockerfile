ARG ROS_DISTRO=humble

FROM ros:${ROS_DISTRO}-ros-base
# FROM luxonis/depthai-ros:v2.8.1-humble 
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
    libasound2-dev \
    ros-${ROS_DISTRO}-rclpy \ 
    ros-${ROS_DISTRO}-rviz2 \
    ros-${ROS_DISTRO}-pcl-ros \
    ros-${ROS_DISTRO}-std-msgs \
    ros-${ROS_DISTRO}-cv-bridge \ 
    ros-${ROS_DISTRO}-image-transport \
    ros-${ROS_DISTRO}-image-transport-plugins \
    ros-${ROS_DISTRO}-rmw-cyclonedds-cpp \
    ros-${ROS_DISTRO}-image-proc \
    ros-${ROS_DISTRO}-rtabmap-slam \ 
    ros-${ROS_DISTRO}-depthai-ros \ 
    gstreamer1.0-plugins-bad \
    alsa-utils \
    mpg123 \
    libmpg123-dev \
    unzip \
    ffmpeg \
    git \
    wget \
    htop \
    python3-pip \
    qtbase5-private-dev \
    libopencv-dev \
    kmod \
    kbd \
    ~nros-humble-rqt*

RUN pip install --upgrade pip && \
    pip install pyserial textual keyboard

RUN apt update && apt upgrade -y && apt install -y \
    ros-$ROS_DISTRO-foxglove-bridge \
    ros-$ROS_DISTRO-bond \
    ros-$ROS_DISTRO-control-msgs \
    ros-$ROS_DISTRO-controller-manager-msgs \
    ros-$ROS_DISTRO-image-transport-plugins \
    ros-$ROS_DISTRO-map-msgs \
    ros-$ROS_DISTRO-nav2-msgs \
    ros-$ROS_DISTRO-tf2-msgs \
    ros-$ROS_DISTRO-robot-localization && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*