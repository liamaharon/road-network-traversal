# Tests for comp20007 assignment 1 2017 sem 1 road-network-traversal
# Written by Liam Aharon

#!/bin/bash

echo "Running all test cases..."
./a1 -p 1 -s 12 -f vicroads.txt > ./my_output/vic-p1-s12-myout.txt
./a1 -p 2 -s 12 -f vicroads.txt > ./my_output/vic-p2-s12-myout.txt
./a1 -p 3 -s 12 -d 4 -f vicroads.txt > ./my_output/vic-p3-s12-d4-myout.txt
./a1 -p 4 -s 12 -d 4 -f vicroads.txt > ./my_output/vic-p4-s12-d4-myout.txt
./a1 -p 5 -s 12 -d 4 -f vicroads.txt > ./my_output/vic-p5-s12-d4-myout.txt

echo "Completed - comparing differences"

echo "Checking part 1"
diff ./my_output/vic-p1-s12-myout.txt ./sample_output/vic-p1-s12.txt
echo "Checking part 2"
diff ./my_output/vic-p2-s12-myout.txt ./sample_output/vic-p2-s12.txt
echo "Checking part 3"
diff ./my_output/vic-p3-s12-d4-myout.txt ./sample_output/vic-p3-s12-d4.txt
echo "Checking part 4"
diff ./my_output/vic-p4-s12-d4-myout.txt ./sample_output/vic-p4-s12-d4.txt
echo "Checking part 5"
diff ./my_output/vic-p5-s12-d4-myout.txt ./sample_output/vic-p5-s12-d4.txt
