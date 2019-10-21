#project(IntelligentAgent-tests)
cmake_minimum_required(VERSION 3.10)

find_package(CxxTest REQUIRED)

if(CXXTEST_FOUND)
    set(SOURCE_FILES InferenceUnittest.cpp InferenceUnittest.h ../../../components/Inference/Inference.cpp ../../../components/KnowledgeBase/KB.cpp ../../../utilities/Model.cpp)
    add_executable(InferenceUnittest ${SOURCE_FILES})
endif()
