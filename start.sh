#If argument "compile"
if [ "$1" = "compile" ]; then
    #Compile
    cd ./build
    ninja
elif [ "$1" = "run" ]; then
    #Run
    cd ./bin
    ./ogl
else
    echo "Usage: ./start.sh [compile|run]"
fi
