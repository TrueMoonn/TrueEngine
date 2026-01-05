#!/bin/bash
git submodule update
if [[ $1 == "--build" || $1 == "-b" ]]
then
    echo "------------BUILD------------"
    if [ ! -d "./build/" ]
    then
        mkdir ./build/ && cd ./build/
        cmake ..
        cd ..
    fi
    cmake --build ./build/ -j
    echo "------------END------------"

elif [[ $1 == "--re-build" || $1 == "-rb" ]]
then
    clear
    echo "------------RE-BUILD------------"
    rm -rf ./build/ ./*.a ./plugins/*.so
    rm -rf include/ECS include/Network
    mkdir ./build/ && cd ./build/
    cmake .. -DDEBUG_ALL=ON
    cmake --build . -j
    cd ..
    echo "------------END------------"

elif [[ $1 == "--build-tests" || $1 == "-t" ]]
then
    clear
    echo "------------TESTS------------"
    rm -rf ./build/ ./*.a ./plugins/*.so
    rm -rf include/ECS include/Network
    mkdir ./build/ && cd ./build/
    cmake .. -DENABLE_TE_TESTS=ON -DENABLE_TE_COVERAGE=ON
    cmake --build . -j
    ctest --output-on-failure
    gcovr --root .. \
        --filter '../src/' \
        --filter '../include/' \
        --html --html-details -o coverage.html
    xdg-open coverage.html
    cd ..
    echo "------------END------------"

elif [[ $1 == "--debug-build" || $1 == "-d" ]]
then
    echo "------------DEBUG------------"
    rm -rf ./build/ ./*.a ./plugins/*.so
    rm -rf include/ECS include/Network
    mkdir ./build/ && cd ./build/
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    cmake --build . -v -j
    cd ..
    echo "------------END------------"

elif [[ $1 == "--clear" || $1 == "-c" ]]
then
    rm -rf ./include/sfml ./include/Sfml.hpp
    rm -rf ./include/display ./include/Display.hpp
    rm -rf ./include/physic ./include/Physic.hpp
    rm -rf ./include/interaction ./include/Interaction.hpp
    rm -rf ./include/entity_spec ./include/EntitySpec.hpp
    rm -rf ./build/ ./*.a ./plugins/*.so
    rm -rf include/ECS include/Network
    cd ./tests/game_test/
    rm -rf ./build ./GameTest ./plugins
    cd ../..

elif [[ $1 == "--game-testing" || $1 == "-gt" ]]
then
    echo "------------GAME TESTING------------"
    cd tests/game_test
    rm -rf ./build/ GameTest ./plugins/
    mkdir ./plugins/ && cp ../../plugins/*.so ./plugins/
    mkdir ./build/ && cd ./build/
    cmake ..
    cmake --build . -j
    cd ..
    ./GameTest
    cd ../..
    echo "------------END------------"

elif [[ $1 == "--style-check" || $1 == "-cs" ]]
then
    echo "------------CS CHECKER------------"
    pip install cpplint
    cpplint --recursive .
    echo "------------END------------"

elif [[ $1 == "--doxygen" || $1 == "-doc" ]]
then
    echo "------------DOXYGEN------------"
    rm -rf doxygen/
    doxygen
    xdg-open doxygen/html/index.html
    echo "------------END------------"

elif [[ $1 == "--help" || $1 == "-h" ]]
then
    echo "To use this executer you must use a flag:
    --build, -b             Build the program with CMake
    --style-check, -cs      Check for coding style using cpplint
    --help, -h              More information about this script
    --doxygen, -doc   Create local documentation site using Doxygen

    << This section delete the old files created by the compilation >>
    --re-build, -rb         Build the program with CMake
    --debug-build, -d       Build the program with debug and verbose
    --clear, -c             Clear files created by the compilation and more
    --game-testing, -gt     Build and launch test game
    --build-test, -t        Launch unit tests with coverage using GTest
"
else
    echo "error: missing or wrong flag
To use this executer you must use a flag:
    --build, -b             Build the program with CMake
    --style-check, -cs      Check for coding style using cpplint
    --help, -h              More information about this script
    --doxygen, -doc   Create local documentation site using Doxygen

    << This section delete the old files created by the compilation >>
    --re-build, -rb         Build the program with CMake
    --debug-build, -d       Build the program with debug and verbose
    --clear, -c             Clear files created by the compilation and more
    --game-testing, -gt     Build and launch test game
    --build-test, -t        Launch unit tests with coverage using GTest
"
fi
