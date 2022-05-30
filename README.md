# Estrutura de dados - Relatório 

## EP - 2: Nas Alturas - Matheus Miranda

- Descrição das estruturas
- Geração dos elementos
- Conclusão

## Descrição das estruturas:

Para fazer o programa foi essencial uma estrutura e algumas funções:

__1. struct BST__
   
   ![image](https://user-images.githubusercontent.com/75645010/169666111-e8098a58-05eb-4f47-b838-c8bd95d04e10.png)

Todo o programa gira em torno desta estrutura que serve tanto para uma BST quanto para uma AVL

__2. BST* avlInsert(BST* raiz, int chave)__

Função que realiza a inserção do nó na árvore, atualiza a altura e o fator de balanceamento de cada nó e garante que a árvore AVL esteja sempre equilibrada, fazendo as rotações necessárias.

![image](https://user-images.githubusercontent.com/75645010/171011301-3ffed9f6-870b-4790-8498-0b1e3910056c.png)


__3. buscaChave(BST* raiz, int chave)__

Função importante para garantir inserção de números distintos

![image](https://user-images.githubusercontent.com/75645010/171011169-4dcb12ff-9c4c-4f8f-826d-4c7de5a1d0ab.png)



## Geração dos elementos da árvore

![image](https://user-images.githubusercontent.com/75645010/170997533-e67c0870-cfa8-4b24-a62b-955144824809.png)

Para garantir que os números gerados fossem distintos, é realizada uma busca do numero gerado e caso ele não seja distinto, sorteia um novo até que o número seja único.

## Conclusão

Após criar diversos experimentos foi interessante ver a diferença entre a altura média das árvores e o tempo de criação de cada árvore.

Com poucas quantidades de nós, entre 50 e 999, o tempo de criação das árvores de ambos tipos é bem parecido, porém já é visivel que a inserção em uma BST é mais rápida que em uma AVL, mas que a altura da AVL é sempre menor pelo fato dela ser equilibrada.

Com uma quantidade de nós entre 1000 e 9999, a diferença fica ainda mais nítida, o tempo de criação de cada árvore AVL passa a ser de 2.5 vezes à 3 vezes mais lenta que o de cada BST, dado que a AVL sempre tenta manter uma altura eficiente.

Com grandes quantidades de nós, entre 10000 e 30000, a diferença entre as alturas é muito aparente e é onde se tem um custo maior de tempo de criação para cada AVL mas é mantida uma altura eficiente para cada árvore.