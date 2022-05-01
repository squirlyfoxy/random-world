#Compile
cd ./build
cmake .. -G Ninja
ninja
# copy assetter to bin folder
cp ./assetter ../../../bin/assetter
