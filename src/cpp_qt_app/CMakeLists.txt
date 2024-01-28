cmake_minimum_required(VERSION 3.8)
project(cpp_qt_app)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB PRO_FORM_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB_RECURSE PRO_INCLUDE_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/*.hpp *.h )
file(GLOB_RECURSE PRO_SOURCES_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

include_directories(
    include
    ${Qt5Widgets_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Generate Qt-related files
qt5_wrap_ui(PROJECT_SOURCES_UI ${PRO_FORM_DIR})
qt5_wrap_cpp(PROJECT_SOURCES_MOC ${PRO_IN})

add_executable(cpp_qt_app 
    ${PRO_SOURCES_DIR} 
    ${PROJECT_SOURCES_UI} 
    ${PROJECT_SOURCES_MOC}
)

ament_target_dependencies(cpp_qt_app
    rclcpp
)

target_link_libraries(cpp_qt_app 
    Qt5::Widgets
)

# Install the executable
install(TARGETS cpp_qt_app
        DESTINATION lib/${PROJECT_NAME})

ament_package()