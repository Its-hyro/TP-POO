if(EXISTS "/Users/doriandrivet/Desktop/dorian/MASTER 1/POO/TD-POO/TP-POO/build/UnitTests[1]_tests.cmake")
  include("/Users/doriandrivet/Desktop/dorian/MASTER 1/POO/TD-POO/TP-POO/build/UnitTests[1]_tests.cmake")
else()
  add_test(UnitTests_NOT_BUILT UnitTests_NOT_BUILT)
endif()
