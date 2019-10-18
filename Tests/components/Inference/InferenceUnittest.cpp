/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_is_valid_position_init = false;
#include "InferenceUnittest.h"

static is_valid_position suite_is_valid_position;

static CxxTest::List Tests_is_valid_position = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_is_valid_position( "InferenceUnittest.h", 9, "is_valid_position", suite_is_valid_position, Tests_is_valid_position );

static class TestDescription_suite_is_valid_position_test_valid_cases : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_is_valid_position_test_valid_cases() : CxxTest::RealTestDescription( Tests_is_valid_position, suiteDescription_is_valid_position, 16, "test_valid_cases" ) {}
 void runTest() { suite_is_valid_position.test_valid_cases(); }
} testDescription_suite_is_valid_position_test_valid_cases;

static class TestDescription_suite_is_valid_position_test_invalid_cases : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_is_valid_position_test_invalid_cases() : CxxTest::RealTestDescription( Tests_is_valid_position, suiteDescription_is_valid_position, 25, "test_invalid_cases" ) {}
 void runTest() { suite_is_valid_position.test_invalid_cases(); }
} testDescription_suite_is_valid_position_test_invalid_cases;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
