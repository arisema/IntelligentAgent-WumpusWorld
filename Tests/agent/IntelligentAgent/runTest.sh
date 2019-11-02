#!/bin/bash
cxxtestgen --error-printer -o IAUnittest.cpp IAUnittest.h
# g++ IAUnittest.cpp ../../../agent/IntelligentAgent/IA.cpp ../../../utilities/DataStructures.h -o IAUnittest
# ./InferenceUnittest
