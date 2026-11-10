# 📚 Sistema de Gerenciamento de Biblioteca 

> Um sistema em C para organizar o acervo de uma biblioteca de forma rápida e eficiente, usando uma **árvore Patricia (Practical Algorithm To Retrieve Information Coded In Alphanumeric)** indexada pelo **id** dos livros. 

---

## 👩‍💻 Integrantes da Dupla

| 👤 Nome | 🎓 Matrícula |
|---|---|
| Ana Paula Ferreira | 6569 |
| Laura Soares do Vale | 6574 |

---

## 📖 Descrição do Problema e da Aplicação Desenvolvida

### 🧩 O problema

Com o crescimento do acervo de uma biblioteca, a gestão manual dos livros tornou-se ineficiente. Processos essenciais, como a localização de títulos para empréstimos e a reorganização dos exemplares devolvidos nas estantes, passaram a exigir um tempo excessivo da equipe.

Quando a quantidade de livros é grande, realizar **buscas sequenciais** se torna **ineficiente**, pois, no pior caso, é necessário percorrer todo o acervo para encontrar um único livro.

### 💡 A solução
Para resolver esse problema, **O Sistema  de Gerenciamento de Biblioteca** foi desenvolvido para automatizar o acervo, otimizando as buscas e garantindo uma devolução rápida e precisa.

O sistema em C organiza o acervo em uma **árvore Patricia**, permitindo **buscas, inserções e remoções eficientes**, mesmo com um acervo grande. Cada livro tem um **id** único, e é por ele que a árvore é percorrida.

O acervo inicial é carregado de um arquivo de texto (`data/livros.txt`), com um livro por linha no formato:

```
título;autor;ano;quantidade;total
```

- `quantidade`: exemplares **disponíveis** na prateleira;
- `total`: exemplares que a biblioteca **possui**. Isso impede que a devolução faça a quantidade passar do que existe de verdade.

O id é gerado automaticamente, em sequência, conforme as linhas são lidas (1, 2, 3...). Livros novos cadastrados pelo teclado continuam a numeração.

Pelo menu, o usuário pode **cadastrar**, **remover**, **listar** e **imprimir** livros, além de **alugar** e **devolver**:

| Opção | Ação |
|---|---|
| 1 | Cadastrar livro |
| 2 | Remover livro |
| 3 | Listar acervo |
| 4 | Imprimir livro |
| 5 | Alugar livro |
| 6 | Devolver livro |
| 0 | Sair |

---

## 🌳 Estrutura de Dados Escolhida e Justificativa Técnica
Para garantir buscas rápidas, optamos pela **árvore Patricia**, por ser uma árvore digital ela dispensa a compração de chaves inteiras, direcionando o percurso através da análise sequencial de bits. Essa abordagem otimiza o tempo de busca. 

### 🔧 Como ela funciona

- A chave é o **id do livro**, um número inteiro. Seus bits são numerados a partir do mais significativo.
- Os **nós internos** guardam apenas o **índice do bit** que será testado: se o bit for `0`, a busca segue para a esquerda; se for `1`, para a direita.
- Os **nós externos** (folhas) guardam o livro completo (título, autor, ano, quantidade e total).
- Ao chegar a uma folha, o sistema **compara o id** para confirmar se é o livro procurado, já que o caminho só leva ao candidato mais provável.
- Os índices **sempre crescem** ao descer pela árvore. É isso que diz onde um novo nó interno deve ser encaixado na inserção.

Exemplo ilustrativo, com ids de 4 bits (`5 = 0101`, `6 = 0110`, `12 = 1100`):

```
        [bit 1]
        /     \
   [bit 3]     12
    /    \
   5      6
```

### ✅ Por que a Patricia?

- 🔑 **Busca direta pelo id:** cada livro tem um id único, e a árvore é percorrida bit a bit por ele. Nas folhas encontramos todas as informações do livro, sem comparações de texto durante a descida.
- ⚡ **Custo limitado pela largura do id:** cada nó interno testa um bit diferente, em ordem crescente, então uma busca nunca passa de tantos testes quanto o número de bits do id, e esse limite **não depende de quantos livros o acervo tem**.
- 🧠 **Sem rotações:** a forma da árvore não depende da ordem de inserção, então não é preciso manter fator de balanceamento nem fazer rotações, como seria numa AVL.
- 🆔 **Títulos repetidos não são problema:** como a chave é o id, dois livros com o mesmo título convivem sem conflito.
- 📋 **Listagem já ordenada:** como a esquerda é bit `0` e a direita é bit `1`, percorrer a árvore da esquerda para a direita mostra os livros em **ordem crescente de id**, sem ordenar nada.
- 💾 **Livro guardado por cópia:** a folha guarda uma cópia do livro, então o sistema não depende da variável usada na leitura.

---

## ⚙️ Descrição das Principais Operações Implementadas

### 🌿 Árvore Patricia (`src/patricia.c`)

As operações mais usadas pelo sistema são **inserir**, **buscar** e **remover**:

| Operação | O que faz |
|---|---|
| `inserir_patricia` | Desce até a folha mais parecida com o id, descobre o **primeiro bit em que os ids diferem** e encaixa um novo nó interno nesse ponto. Recusa ids repetidos. |
| `buscar_patricia` | Desce pelos bits do id até uma folha e confere o id. Devolve um ponteiro para o livro dentro da árvore, ou `NULL`. |
| `remover_patricia` | Localiza a folha, remove-a e coloca o **irmão** no lugar do nó pai. |
| `cria_patricia` / `destruir_patricia` | Criam a árvore vazia e liberam toda a memória. |
| `imprimir_patricia` | Percorre as folhas e imprime cada livro. |

### 📕 Livro (`src/livro.c`)
| Operação | O que faz |
|---|---|
| `criar_livro` | lê **uma linha** do `livros.txt` e monta o livro com seus campos e o id. Os livros lidos são inseridos na árvore quando o programa abre.
| `gerar_id` |devolve o próximo id e avança o contador.
| `imprimir_livro` | mostra um livro (`id | título | autor | ano | disponíveis | total`).
|  `registrar_emprestimo` / `registrar_devolucao` | alteram a quantidade de um livro, recusando o empréstimo quando não há exemplares e a devolução quando todos já estão na biblioteca.

### 🏛️ Biblioteca (`src/biblioteca.c`)

Reúne as funções que fazem o **menu de operações** funcionar:

| Operações | O que faz |
|---|---|
| `Adicionar livro` | o usuário digita os dados pelo teclado, e o livro é inserido na árvore com um id novo.
| `Remover livro` | usa a busca da Patricia para verificar se o livro existe, **recusa a remoção se ainda houver exemplares alugados** e, caso contrário, remove o livro da árvore.
| `Listar acervo` | imprime todos os livros da árvore.
| `Imprime livro` | busca um livro pelo id e imprime as suas informações, ou avisa que ele não existe.
| `Alugar livro` | usa a busca da Patricia para verificar se o livro existe e se ainda há exemplares disponíveis; depois, diminui a quantidade.
| `Devolver livro` | usa a busca para verificar se o livro existe e se há algum exemplar fora; depois, aumenta a quantidade.

---

## 🗃️ Organização dos Arquivos do Projeto

```
📦 SistemaDeGerenciamentoDeBiblioteca/
 ┣ 📂 data/
 ┃ ┗ 📄 livros.txt      # Acervo inicial 
 ┣ 📂 include/
 ┃ ┣ 📄 biblioteca.h    # Funções do sistema 
 ┃ ┣ 📄 livro.h         # Struct Livro e funções 
 ┃ ┗ 📄 patricia.h      # Árvore Patricia
 ┣ 📂 main/
 ┃ ┗ 📄 main.c          # Programa principal 
 ┣ 📂 src/
 ┃ ┣ 📄 biblioteca.c
 ┃ ┣ 📄 livro.c
 ┃ ┗ 📄 patricia.c
 ┣ 📂 tests/
 ┃ ┣ 📄 teste.h         
 ┃ ┗ 📄 teste.c         # Testes automatizados
 ┣ 🛠️ Makefile          # Automatização da compilação e dos testes
 ┗ 📝 README.md         # Documentação do projeto
```

---

## 🛠️ Instruções de Compilação e Execução

Criamos um `Makefile` para facilitar a compilação e execução de todos os arquivos:

| Comando | O que faz |
|---|---|
| `make` | compila, **roda os testes** e, se todos passarem, abre o menu |
| `make test` | roda só os testes |
| `make run` | abre só o menu |
| `make clean` | apaga o executável |

Se algum teste falhar, o `make` para antes de abrir o menu.

---

## 🧪 Descrição dos Testes Realizados

### 🖐️ Manualmente pelo menu

O sistema foi testado **manualmente pelo menu**:

- ✅ cadastro de um livro novo e conferência na listagem;
- ✅ remoção de um livro e conferência de que ele sumiu da listagem;
- ✅ impressão de um livro pelo id, existente e inexistente;
- ✅ aluguel e devolução de um livro existente, com a quantidade subindo e descendo corretamente;
- ✅ devolução recusada quando todos os exemplares já estão na biblioteca;
- ✅ entradas inválidas (letras, só Enter ou número inexistente) no menu e nos ids.

### 🤖 Automaticamente pelo arquivo `tests/teste.c`

O arquivo cria suas próprias árvores, **sem depender do `livros.txt`**, e usa a função `verificar`, que imprime `[OK]` ou `[FALHA]` para cada conferência e conta os resultados. No final, mostra **TESTE APROVADO!** ou **TESTE REPROVADO!**. Quando algum teste falha, o programa termina com código de erro.

**Testes da Patricia** (`teste_patricia`):

| Teste | O que confere |
|---|---|
| inserir livro novo | a inserção em árvore vazia é aceita |
| id repetido | a inserção de um id que já existe é recusada |
| buscar id existente | a busca encontra o livro inserido |
| buscar id inexistente | a busca devolve `NULL` para um id que não existe |

**Testes de aluguel e devolução** (`teste_aluguel_devolucao`), com um livro de 2 exemplares:

| Teste | O que confere |
|---|---|
| inserir livro para o teste | o livro entra na árvore |
| alugar com exemplar disponível | o aluguel é aceito e a quantidade cai para 1 |
| alugar o último exemplar | o aluguel é aceito e a quantidade cai para 0 |
| alugar livro esgotado | o aluguel é **recusado** e a quantidade continua 0 |
| devolver um livro | a devolução é aceita e a quantidade sobe para 1 |
| devolver o outro exemplar | a devolução é aceita e a quantidade volta para 2 |
| devolver com tudo na biblioteca | a devolução é **recusada** e a quantidade continua 2 |
| alugar id inexistente | o aluguel é recusado |
| devolver id inexistente | a devolução é recusada |

**Resultado:** 19 verificações, 19 OK, 0 falhas.

---

## 📊 Resultados Experimentais e Análise

### ✅ Resultado dos testes

Depois das correções abaixo, o teste automatizado passou por inteiro: **19 verificações, 19 OK, 0 falhas** (`TESTE APROVADO!`).

### 🐛 Erros encontrados e corrigidos

Durante o desenvolvimento tivemos vários erros, e os testes e os avisos do compilador nos ajudaram a encontrá-los:

| Erro | Como foi encontrado | Correção |
|---|---|---|
| A devolução aumentava a quantidade em **2** em vez de 1 | o teste automatizado mostrou a quantidade indo de 0 direto para 2 numa única devolução | a devolução passou a ser registrada uma única vez em `devolver_livro` |
| `devolver_livro` e `alugar_livro` terminavam sem devolver valor | avisos do compilador (`control reaches end of non-void function`) | cada caminho da função passou a ter o seu `return` |
| O título do livro cadastrado saía vazio | o `scanf` da opção do menu deixava o Enter no teclado, e o `fgets` seguinte o lia | `limpar_buffer` depois de cada `scanf` e leituras do cadastro com `fgets` + `sscanf` |
| Uma letra digitada no menu ou no id repetia a ação anterior | teste manual com entradas inválidas | o retorno do `scanf` passou a ser conferido, e ganhamos o `default` do menu |
| Um cadastro cancelado mostrava um livro com lixo | teste manual | o retorno de `adicionar_livro` é conferido antes de mostrar algo |
| Erros de compilação (`unknown type name`) entre `patricia.h` e `biblioteca.h` | compilador: cada header incluía o outro | a struct `Livro` foi para o `livro.h`, e a dependência passou a andar em um sentido só |
| `multiple definition` no linker | funções com corpo escrito dentro de um `.h` | os corpos foram para arquivos `.c` |
| O próprio teste travava | o teste alugava um livro que nunca tinha sido inserido, e os valores esperados estavam errados | o livro passou a ser inserido antes, e os valores esperados foram corrigidos |

O principal aprendizado: o **bug da devolução** não aparecia no teste manual (com um exemplar fora, a segunda soma era recusada sem aviso) e só foi percebido pelo teste automatizado, com dois exemplares alugados.

---

## ⚠️ Limitações Conhecidas e Possíveis Melhorias

### Limitações

- 🔢 **Busca só pelo id:** queríamos organizar a árvore pelo título do livro, mas o id facilitou muito a implementação e permite títulos repetidos. Em contrapartida, o usuário precisa saber o id para alugar, devolver, remover e consultar um livro (a listagem do acervo mostra os ids).
- 📏 **Id de largura fixa:** a chave tem um número fixo de bits, então existe um id máximo aceito pela árvore.
- 🔤 **Acentos no Windows:** o terminal pode exibi-los de forma incorreta se não estiver em UTF-8.
- 💾 **Alterações não são salvas:** cadastros, remoções e aluguéis existem só enquanto o programa está aberto.

### Possíveis melhorias

- 🔎 **Pesquisa por título:** a pessoa digitaria parte do título e as opções apareceriam. Por exemplo, ao digitar `harry`, seriam listados todos os livros com `harry` no título e seus ids. Para ser rápida em acervos grandes, a ideia seria um segundo índice, por palavra.
- ❓ **Confirmação antes de remover** um livro, para evitar perder um registro por engano.
- ✅ **Validações mais rígidas no cadastro:** título ou autor vazios, ano e quantidade fora de uma faixa válida.
- 👤 **Cadastro de clientes:** cada cliente poderia alugar até 3 livros e não poderia alugar duas vezes o mesmo id, com histórico de aluguéis.
- 💾 **Salvar alterações no arquivo** ao sair, para que cadastros, remoções e aluguéis não se percam.

---