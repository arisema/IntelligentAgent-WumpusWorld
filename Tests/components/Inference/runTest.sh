#!/bin/bash
cxxtestgen --error-printer -o InferenceUnittest.cpp InferenceUnittest.h
# mkdir build/
# cd build
# cmake ..
# # cd ../
g++ InferenceUnittest.cpp ../../../components/Inference/Inference.cpp ../../../components/KnowledgeBase/KB.cpp ../../../utilities/Model.cpp -o InferenceUnittest
# make
./InferenceUnittest
