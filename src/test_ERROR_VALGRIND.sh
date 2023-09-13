#!/bin/bash
echo "Please wait! Valgrind detecting your code..."
valgrind  --log-file=RESULT_VALGRIND.txt ./test.out > temp.txt
SUCCESS=`grep -e "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" -c RESULT_VALGRIND.txt`
FAIL=`grep -e "ERROR SUMMARY: [1-9]* errors from [1-9]* contexts (suppressed: [0-9]* from [0-9]*)" -c RESULT_VALGRIND.txt`
TOTAL=`grep -e "ERROR SUMMARY:" -c RESULT_VALGRIND.txt`
grep -e "ERROR SUMMARY: [1-9]* errors from [1-9]* contexts (suppressed: [0-9]* from [0-9]*)" -n RESULT_VALGRIND.txt
rm RESULT_VALGRIND.txt
rm temp.txt

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "TOTAL: $TOTAL"
