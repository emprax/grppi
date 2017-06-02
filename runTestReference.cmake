# Execute test and capture the stdout/stderr
execute_process(
  COMMAND ${TEST_PROGRAM} 
  OUTPUT_FILE ${TEST_OUTPUT}
  ERROR_VARIABLE TEST_ERROR
  RESULT_VARIABLE TEST_RESULT
  )

# If the returned value is !=0 error message
if( TEST_RESULT )
  message( FATAL_ERROR "Failed: Test program ${TEST_PROGRAM} exited != 0.\n${TEST_ERROR}" )
endif( TEST_RESULT )

message( "Passed: The output of ${TEST_PROGRAM} matches ${TEST_REFERENCE}" )

