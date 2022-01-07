# Set the arguments of each of the options for compiling
# our source code.
COMPILER="g++"
ARGS="-g -std=c++17"
SRC="./src/*.cpp"
INCLUDE="./include"
BINARY="./bin/prog"
LIBS="-lSDL2 -lSDL2_ttf -lSDL2_mixer -ldl"

# Echo out the platform we are compilng on.
echo "Compiling on ${OSTYPE}"

# Build the compile string
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "Compiling on Linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Compilng on Mac"
    INCLUDE="./include -I/Library/Frameworks/SDL2.framework/Headers"
    LIBS="-F/Library/Frameworks -framework SDL2"
elif [[ "$OSTYPE" == "mysys" ]] ; then
    echo "Compiling on Windowsi(mysys)"
    LIBS="-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer"
else
    echo "Not sure what operating sytstem to build for"
fi

COMPILE="${COMPILER} ${ARGS} ${SRC} -I ${INCLUDE} -o ${BINARY} ${LIBS}"

# Write out the compile string for the user to see
echo ${COMPILE}

# Evaluate the compile string
eval $COMPILE
