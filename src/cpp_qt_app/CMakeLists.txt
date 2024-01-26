cmake_minimum_required(VERSION 3.8)
project(cpp_qt_app)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

# setup sources
file(GLOB PRO_SOURCE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS  src/*.cpp)
file(GLOB PRO_UI_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS  ui/*.ui)
file(GLOB PRO_INCLUDE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS  include/*.h *.hpp)
file(GLOB PRO_RESOURCE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS  resource/*.qrc)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

qt5_wrap_ui(QT_UI_HPP ${PRO_UI_DIR})
qt5_wrap_cpp(QT_MOC_HPP ${PRO_INCLUDE_DIR})
qt5_add_resources(QT_RESOUCE_HPP ${PRO_RESOURCE_DIR})
include_directories(
	include/
	${CMAKE_CURRENT_BINARY_DIR}
)
add_executable(${PROJECT_NAME}
    ${PRO_SOURCE_DIR}
    ${PRO_INCLUDE_DIR}
    ${PRO_UI_DIR}
    ${QT_MOC_HPP}
    ${QT_RESOUCE_HPP}
  )


ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  std_msgs
  )

target_link_libraries(${PROJECT_NAME} 
  Qt5::Core
  Qt5::Quick
  Qt5::Widgets
  )

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
  )

ament_package()
