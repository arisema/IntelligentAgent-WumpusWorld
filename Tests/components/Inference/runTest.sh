#!/bin/bash
cxxtestgen --error-printer -o InferenceUnittest.cpp InferenceUnittest.h
g++ -o InferenceUnittest InferenceUnittest.cpp
./InferenceUnittest
