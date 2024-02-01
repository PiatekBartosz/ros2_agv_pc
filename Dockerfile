ARG ROS_DISTRO=humble
FROM ros:${ROS_DISTRO}-ros-base

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
    libopencv-dev

# RUN pip3 install aqtinstall -y


