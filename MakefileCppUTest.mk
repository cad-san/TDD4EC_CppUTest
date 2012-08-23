#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = TDD4EC_CppUTest

#--- Inputs ----#
CPPUTEST_HOME = CppUTest
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = .

SRC_DIRS = \
	src/util\
	src/LedDriver\
	src/HomeAutomation\
	src/HomeAutomation/devices

TEST_SRC_DIRS = \
	.\
	tests\
	tests/HomeAutomation
#	tests/stdio\

	
INCLUDE_DIRS =\
	.\
	$(CPPUTEST_HOME)/include\
	include/HomeAutomation\
	include/HomeAutomation/devices\
	include/LedDriver\
	mocks\

MOCKS_SRC_DIRS = \
	mocks\
	mocks/HomeAutomation\
	
CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default -Werror 
#CPPUTEST_CFLAGS = -std=c89 
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
LD_LIBRARIES = -lpthread
	
  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

