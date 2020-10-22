# Build

g++ -Wall -Werror -Wextra --coverage test/$1/*.cpp -o test_runner -lgtest -lgtest_main -pthread

# Run

./test_runner

# Coverage

mv *.gc* test/$1/

printf "\n**************** Coverage Report ***************\n\n"

gcov -r test/$1/*.cpp 
gcovr -r . --html -o index.html

# Clean

rm *.gc*
rm test_runner
cd test/$1/
rm *.gc*
cd ../../