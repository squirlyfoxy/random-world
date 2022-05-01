#If argument "compile"
if [ "$1" = "compile" ]; then
    #Compile
    echo "Building Assetter (1/2)..."
    cp -r ./lib/zip ./external/assetter/zip
    cp -r ./lib/SQLiteCpp ./external/assetter/SQLiteCpp

    cd ./external/assetter
    sh ./start.sh
    cd ../../
    echo "Building Engine   (2/2)..."
    cd ./build
    cmake .. -G Ninja
    ninja

    cd ../bin
    echo "STP1 - Starting Assetter..."
    ./assetter
elif [ "$1" = "run" ]; then
    #Run
    cd ./bin
    ./ogl
else
    echo "Usage: ./start.sh [compile|run]"
fi
