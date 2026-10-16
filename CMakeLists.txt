cmake_minimum_required(VERSION 3.8)
project(mes_ob9_fekrendszer)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# 1. radar_node lefordítása
add_executable(radar_node src/radar_node.cpp)
ament_target_dependencies(radar_node rclcpp std_msgs)

# 2. brake_node lefordítása
add_executable(brake_node src/brake_node.cpp)
ament_target_dependencies(brake_node rclcpp std_msgs)

# Futtatható fájlok telepítése
install(TARGETS
  radar_node
  brake_node
  DESTINATION lib/${PROJECT_NAME}
)

# Launch mappa telepítése
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()