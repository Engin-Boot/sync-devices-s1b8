# Build

if [ $1 == TestPatient ]; then
    g++ -Wall -Werror --coverage test/$1/*.cpp -o test_runner -lgtest -lgtest_main -pthread
fi

if [ $1 == UnitTests ]; then
    g++ -Wall -Werror --coverage test/$1/*.cpp -o test_runner -lgtest -lgtest_main -pthread -lpaho-mqtt3as
fi

if [ $1 == IntegrationTests ]; then
    g++ -Wall -Werror --coverage test/$1/*.cpp Patient/*.cpp -o test_runner -lgtest -lgtest_main -pthread -lpaho-mqtt3as
fi

# Run

./test_runner

# Coverage

mv *.gc* test/$1/

printf "\n**************** Coverage Report ***************\n\n"

gcov -r test/$1/*.cpp 
gcovr -r . --html -o $2.html

# Clean

rm *.gc*
rm test_runner
cd test/$1/
rm *.gc*
cd ../../