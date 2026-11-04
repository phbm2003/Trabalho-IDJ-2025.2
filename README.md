# Desenvolvimento de jogo do zumbi com C++ e SDL2

Projeto em equipe desenvolvido na disciplina de Introdução ao Desenvolvimento de Jogos (2025/2).  

Principais tecnologias:  
- C++ para implementação da lógica do jogo.  
- SDL2 para recursos gráficos e interação.  
- CMake para configuração e gerenciamento da compilação.  
- Git/GitHub para controle de versão e colaboração.  


rmdir /S /Q build 


mkdir build


cd build


cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..


cmake --build .


(ADICIONAR ARQUIVOS "SDL2.dll", "SDL2_image.dll", "SDL2_mixer.dll" e "SDL2_ttf.dll" A PASTA build/bin)

(em build executar: )


.\bin\trabalho1.exe
