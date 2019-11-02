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
bool suite_go_init = false;
#include "IAUnittest.h"

static go suite_go;

static CxxTest::List Tests_go = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_go( "IAUnittest.h", 9, "go", suite_go, Tests_go );

static class TestDescription_suite_go_test_cases1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_go_test_cases1() : CxxTest::RealTestDescription( Tests_go, suiteDescription_go, 23, "test_cases1" ) {}
 void runTest() { suite_go.test_cases1(); }
} testDescription_suite_go_test_cases1;

static class TestDescription_suite_go_test_cases2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_go_test_cases2() : CxxTest::RealTestDescription( Tests_go, suiteDescription_go, 70, "test_cases2" ) {}
 void runTest() { suite_go.test_cases2(); }
} testDescription_suite_go_test_cases2;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
