rmdir /S /Q build 


mkdir build


cd build


cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..


cmake --build .


(ADICIONAR ARQUIVOS "SDL2.dll", "SDL2_image.dll", "SDL2_mixer.dll" e "SDL2_ttf.dll" A PASTA build/bin)

(em build executar: )


.\bin\trabalho1.exe
