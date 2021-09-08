# Trabalho de Software Básico

Trabalho da matéria de Software Básico  
14/0065032 - Pedro Henriques Nogueira  
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
Sugestão de comando (Hello World):  
```make limpa && make debug && make cppcheck && ./main.exe default.class```  

#### (./fonte/) lib, include e src

Organização que o makefile faz:  

* lib - Recebe bibliotecas importadas  
* include - Onde vão os headers (nosso caso, .h's)  
* src - Onde vai o código (.cpp's)  
* bin - Recebe arquivos gerados de objeto (.o's)  

#### (./fonte/) .classes e output.txt

Arquivos do funcionamento do programa. Basicamente, é escolhido um dos .class disponíveis como input do programa para então receber como output do programa o arquivo output.txt

### ./Esse README.md

Vamos sempre atualizar, se atentando ao formato markdown dele. Inclusive os espaços no final das linhas!!!  

## Estilo

O [VSCode](https://code.visualstudio.com/) tem uma ótima integração com o [WSL2](https://ubuntu.com/wsl), por isso vou usar E RECOMENDO seu uso também.  
Nele vou estar usando [a extensão de C++ mais famosa lá](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) e vou configurar para usar o estilo da Google com 120 colunas por linha.  

## Conteúdo do Projeto

Esse projeto consiste no Leitor/Exibidor de classes Java. O programa basicamente pega um arquivo do tipo .class já compilado pelo javac, lê suas sequências de bytecode e as interpreta para o contexto da classe Java do qual esse .class foi tirado, então imprimindo essas informações no arquivo output.txt.  

### Leitura

Existe uma sequência rigorosa a ser seguida para a leitura do bytecode do .class, e ela se encontra no arquivo [classfile.png](https://github.com/bananahell/JVM-Software-Basico/blob/master/classfile.png). Os primeiros 4 bytes servem para o Magic Number, então os próximos 2 bytes servem para o Minor Version, os próximos 2 bytes para Major Version, os próximo 2 bytes para o tamanho da Constant Pool, e assim por diante.  
Esses dados são lidos para estruturas presentes no código do programa para então serem usados logo em seguida.  

### Exibição

Lidos os dados do bytecode do .class, agora são exibidas as informações extraídas disso tudo. Existem várias variáveis que são simplesmente exibidas como elas estão no bytecode, mas existem vários campos e números que na verdade são indíces que apontam para um lugar que contenha suas informações equivalentes.  

Agora vou explicar os argumentos que estão presentes no output.txt:  

#### Magic Number, Minor Version, Major Version

O Magic Number serve para confirmar que essa classe vai seguir as especificações Java de compilação, então ele é necessário nesse começo. Ele é igual a ```0xcafebabe```.  
As Minor e Major Versions são argumentos que especificam a versão de Java usada para compilar o programa.  

#### Constant Pool

A Constant Pool serve como um mapa para vários argumentos constantes presentes dentro do programa. Vários aspectos se referenciam de volta à Constant Pool, então é importante sempre mantê-la por perto.  
Dentro dela existem vários tipos de dados, como MethodRef, Class, FieldRef, enfim, todos reconhecidos por sua [tag no começo de sua estrutura](https://github.com/bananahell/JVM-Software-Basico/blob/master/tagsdeconstantes.png). Quase todos eles contêm índices que referenciam um tipo específico de informação também presente na Constant Pool, com exceção do tipo UTF8, que é o "passo final" dessa procura, podendo-se assim finalmente ler a informação procurada.  
Por exemplo, Class contém em sua estrutura um índice para seu nome. Só checar que variável está presente nesse índice não é o suficiente para saber seu nome, além do mais ele é um índice para o tal nome, então você tem que procurar na Constant Pool a posição desse índice aí para então achar que lá existe uma estrutura de UTF8, que contém finalmente o nome dessa classe escrito.  
Existem algumas situações muito... interessantes no manejo dessa Constant Pool, mas se atentando a quais índices você está usando te garante as informações que você procura.  

#### Access Flag, This Class, Super Class

Essa situação de [Access Flag](https://github.com/bananahell/JVM-Software-Basico/blob/master/fieldsdeacesso.png) é a primeira ocorrência de várias na análise de um .class. Ele é um número que determina quais tipos de acesso você tem a uma estrutura, o que nesse caso é o da própria classe sendo analisada. Esse número contém em seus bits informações sobre se a estrutura é static, public, protected, etc.  
This Class contém um índice que, se lido da Constant Pool, mostra o nome da classe sendo analisada nesse código.  
Super Class, do mesmo jeito que This Class, contém um índice a ser lido na Constant Pool, mas esse mostra a classe da qual sua classe extende, sua super class.  

#### Interfaces

Aqui são listadas as interfaces da qual a classe se aproveita para sua implementação. De novo, só os índices estão presentes aqui, que são usados para referenciar à Constant Pool para achar o nome da interface desejada.  

#### Fields

Os campos da classe são referenciados aqui. Na estrutura de um campo de classe, estão presentes os índices de seu nome e tipo, que é referencidao na Constant Pool, seu Access Flag, que é o número que determina seus modos de acesso, e sua quantidade de atributos.  

#### Methods

Aqui se encontram os métodos dessa classe. Cada estrutura de método contém uma enormidade de informações, sendo elas o nome do método, seu descritor, contendo seu tipo de retorno e os tipos das variáveis de entrada do método, a Access Flag que dita seus modos de acesso, tabelas de variáveis e tabelas de linhas, representadas por índices e presentes no Constant Pool, e todo o bytecode do assembly gerado pela compilação do programa Java. Esse último é muito interessante porque ele também tem índices a serem interpretados, mas esses índices não se encontram na Constant Pool como muitas vezes acontece durante o código, mas sim numa [tabela de instruções bytecode Java oficial da linguagem](https://en.wikipedia.org/wiki/List_of_Java_bytecode_instructions). Esse projeto implementou essa tabela inteira para que o nome do comando e suas variáveis ficassem disponíveis imediatamente para exibição dos comandos usados nos métodos analisados.  

#### Attributes

Uma lista de atributos está presente aqui no final da exibição.  
Vou ser bem sincero e falar que não entendi essa porra. Me processe, o git é meu.  
O máximo que entendi é que esses atributos são atrelados à classe completa em si, e também percebi que sempre há presente um atributo SourceFile que sempre vem seguido do nome do arquivo .java que foi compilado.  
