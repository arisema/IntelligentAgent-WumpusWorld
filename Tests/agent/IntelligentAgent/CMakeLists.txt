#project(IntelligentAgent-tests)
cmake_minimum_required(VERSION 3.10)

find_package(CxxTest REQUIRED)

if(CXXTEST_FOUND)
    set(SOURCE_FILES IAUnittest.cpp IAUnittest.h ../../../agent/IntelligentAgent/IA.cpp ../../../components/Inference/Inference.cpp ../../../components/KnowledgeBase/KB.cpp ../../../components/Sensor/Sensor.cpp ../../../components/Actuator/Actuator.cpp ../../../utilities/DataStructures.h ../../../utilities/Model.cpp)
    add_executable(IAUnittest ${SOURCE_FILES})
endif()
