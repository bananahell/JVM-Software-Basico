# Trabalho de Software Básico

Trabalho da matéria de Software Básico  
14/0065032 - Pedro Nogueira  
18/0112520 - Paulo Mauricio Costa Lopes  
18/0046926 - Mariana Borges de Sampaio  
15/0010290 - Gabriel Nazareno Halabi  
UnB - 2021/1  

## Especificações

### ./PDF's e imagens

Os PDF's e imagens do professor estão na raiz do projeto. Qualquer coisa a mais que aparecer, vamos salvar aqui.  

### ./fonte

Pasta com todo o código do trabalho.  

#### ./fonte/makefile

Contém vários comandos, mas só precisa de um ```make ajuda``` na console para que as mostre.  
Basicamente, se compila com ```make debug``` ou ```make release```, se roda o [cppcheck](https://cppcheck.sourceforge.io/) com ```make cppcheck``` e se executa o programa depois de compilado com ```make executa```.  
Note que desse jeito um arquivo ```default.class``` presente na pasta fonte será lido. Para ler outro arquivo .class presente na pasta fonte, deve-se rodar manualmente o comando ```./main.exe``` seguido do nome do arquivo.  

#### (./fonte/) lib, include e src

Organização que o makefile faz:  

* lib - Recebe bibliotecas importadas  
* include - Onde vão os headers (nosso caso, .h's)  
* src - Onde vai o código (.cpp's)  
* bin - Recebe arquivos gerados de objeto (.o's)  

### ./Esse README.md

Vamos sempre atualizar, se atentando ao formato markdown dele. Inclusive os espaços no final das linhas!!!  

## Estilo

O [VSCode](https://code.visualstudio.com/) tem uma ótima integração com o [WSL2](https://ubuntu.com/wsl), por isso vou usar E RECOMENDO seu uso também.  
Nele vou estar usando [a extensão de C++ mais famosa lá](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) e vou configurar para usar o estilo da Google com 120 colunas por linha.  