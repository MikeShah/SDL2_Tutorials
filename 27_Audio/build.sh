COMPILE="g++ -g -std=c++17 ./src/*.cpp -I./include -o ./bin/prog -lSDL2 -ldl"
echo ${COMPILE}
eval $COMPILE
