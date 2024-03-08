# Makefile for building ROS2 AGV project
SHELL := /bin/bash
PROJECT_NAME := ROS2_AGV_PC
BUILD_DIR := build
INSTALL_DIR := install
LOG_DIR := log

# Source setup file
SOURCE_SETUP := . /opt/ros/humble/setup.bash

# Msg packages (need to be built and sourced first)
MSG_PCKG := interfaces

# Targets
.PHONY: all clean

# Default target
all: build

# Build target
build:
	@. /opt/ros/humble/setup.bash
	@mkdir -p $(BUILD_DIR) $(INSTALL_DIR) $(LOG_DIR)
	@colcon build --packages-select $(MSG_PCKG)
	@. $(INSTALL_DIR)/setup.bash
	@colcon build 

# Clean target
clean:
	@echo "Cleaning $(PROJECT_NAME) build files..."
	@rm -rf $(BUILD_DIR) $(LOG_DIR) $(INSTALL_DIR)
