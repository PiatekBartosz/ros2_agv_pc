ARG ROS_DISTRO=humble

# Copyright (c) 2022, NVIDIA CORPORATION.  All rights reserved.
#
# NVIDIA CORPORATION and its licensors retain all intellectual property
# and proprietary rights in and to this software, related documentation
# and any modifications thereto.  Any use, reproduction, disclosure or
# distribution of this software and related documentation without an express
# license agreement from NVIDIA CORPORATION is strictly prohibited.
FROM nvcr.io/nvidia/isaac/ros:x86_64-ros2_humble_bcf535ea3b9d16a854aaeb1701ab5a86

# FROM ros:${ROS_DISTRO}-ros-base
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
    libopencv-dev
