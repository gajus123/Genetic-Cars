cmake_minimum_required(VERSION 3.10)

project(Genetic-Cars)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -O3")

include_directories(include)

find_package(Box2D REQUIRED)
include_directories(${Box2D_INCLUDE_DIR})
find_package(Qt5Core REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})
find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
find_package(Qt5Charts REQUIRED)
include_directories(${Qt5Charts_INCLUDE_DIRS})

set(SOURCE_FILES
    src/Base.cc
    src/Body.cc
    src/Ground.cc
    src/GroundGenerator.cc
    src/Loop.cc
    src/MainWindow.cc
    src/ObjectsFactory.cc
    src/Simulation.cc
    src/SimulationView.cc
    src/Statistics.cc
    src/StatisticView.cc
    src/Vector2.cc
    src/Vehicle.cc
    src/Watchdog.cc
    src/Wheel.cc
    src/World.cc

    src/MainWindow.ui

    include/algorithm/Gene.hpp
    include/algorithm/Genotype.hpp
    src/algorithm/Population.cpp
    src/algorithm/PopulationWrapper.cpp
    include/algorithm/PopulationWrapper.h

    include/Loop.h
    include/MainWindow.h
    include/Simulation.h
    include/StatisticView.h
    include/Statistics.h
    include/Watchdog.h
)

set(TEST_FILES
    tests/Body_test.cc
    tests/Gene_test.cc
    tests/Ground_test.cc
    tests/GroundGenerator_test.cc
    tests/ObjectsFactory_test.cc
    tests/Population_test.cc
    tests/Vehicle_test.cc
    tests/Wheel_test.cc

    tests/test_main.cc
)



add_executable(${PROJECT_NAME} ${SOURCE_FILES} src/main.cc)
target_link_libraries(${PROJECT_NAME} ${Qt5Core_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Qt5Charts_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${BOX2D_LIBRARIES})
add_executable(${PROJECT_NAME}_tests ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(${PROJECT_NAME}_tests ${Qt5Core_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_tests ${Qt5Widgets_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_tests ${Qt5Charts_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_tests ${BOX2D_LIBRARIES})
