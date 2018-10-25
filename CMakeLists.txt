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
        src/physics/objects/Base.cc
        src/physics/objects/Body.cc
        src/physics/objects/Ground.cc
        src/physics/objects/GroundGenerator.cc
        src/simulation/Loop.cc
    src/MainWindow.cc
        src/physics/objects/ObjectsFactory.cc
        src/simulation/Simulation.cc
        src/ui/SimulationView.cc
    src/Statistics.cc
        src/ui/StatisticView.cc
    src/Vector2.cc
        src/physics/objects/Vehicle.cc
        src/simulation/Watchdog.cc
        src/physics/objects/Wheel.cc
        src/physics/World.cc

        src/ui/MainWindow.ui

    include/algorithm/Gene.hpp
    include/algorithm/Genotype.hpp
    src/algorithm/Population.cpp
    src/algorithm/PopulationWrapper.cpp
    include/algorithm/PopulationWrapper.h

        include/simulation/Loop.h
    include/MainWindow.h
        include/simulation/Simulation.h
        include/ui/StatisticView.h
    include/Statistics.h
        include/simulation/Watchdog.h
)

set(TEST_FILES
        tests/physics/objects/Body_test.cc
        tests/algorithm/Gene_test.cc
        tests/physics/objects/Ground_test.cc
        tests/physics/objects/GroundGenerator_test.cc
        tests/physics/objects/ObjectsFactory_test.cc
        tests/algorithm/Population_test.cc
        tests/physics/objects/Vehicle_test.cc
        tests/physics/objects/Wheel_test.cc

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
