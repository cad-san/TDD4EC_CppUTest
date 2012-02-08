# this is set up to by default to make the top level and test with CppUTest
all: codeCppUTest

clean: cleanCodeCppUTest

cleanCode: cleanCodeCppUTest 

codeCppUTest: CppUTest CppUTestExt
	make -i -f MakefileCppUTest.mk 

cleanCodeCppUTest:
	make -i -f MakefileCppUTest.mk clean
	
CppUTest: CppUTest/lib/libCppUTest.a

CppUTestExt: CppUTest/lib/libCppUTestExt.a

CppUTest/lib/libCppUTest.a:
	pwd
	make -i -C CppUTest

CppUTest/lib/libCppUTestExt.a:
	make -i -C CppUTest extensions
