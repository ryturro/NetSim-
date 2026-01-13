# CMake generated Testfile for 
# Source directory: C:/Users/afolw/Documents/ZPSiO/NetSim
# Build directory: C:/Users/afolw/Documents/ZPSiO/NetSim/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MyProjectTests "C:/Users/afolw/Documents/ZPSiO/NetSim/build/unit_tests.exe")
set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/afolw/Documents/ZPSiO/NetSim/CMakeLists.txt;46;add_test;C:/Users/afolw/Documents/ZPSiO/NetSim/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
