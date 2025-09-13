# Trabalho-IDJ-2025.2

rmdir /S /Q build   -- deletar e criar nova build

mkdir build

cd build


cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..

cmake --build .

.\bin\trabalho1.exe
