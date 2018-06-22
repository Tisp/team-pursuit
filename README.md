# Team Pursuit

### 1 Problema

Uma das varias modalidades de ciclismo realizada em velódromos é a [perseguição por equipe](https://en.wikipedia.org/wiki/Team_pursuit). O objetivo deste EP sera simular essa modalidade. Na perseguição por equipe, cada equipe, contendo 4 ciclistas, inicia a prova em lados opostos do velodromo. Os 4 ciclistas de cada equipe ficam lado-a-lado na largada e logo depois, para obter uma vantagem aerodinamica, ficam enfileirados com mudanças regulares das posições de modo que o primeiro ciclista mude de tempos em tempos e os demais, que ficam atras, possam economizar energia. A equipe que vence a prova e aquela cujo terceiro ciclista, após 4Km (16 voltas num velodromo de 250 metros) cruzar primeiro a linha de chegada (que e relativa a linha de largada da equipe). A prova tambem termina se o terceiro ciclista de uma equipe ultrapassar o terceiro ciclista da outra equipe.

A sua tarefa neste EP e simular a corrida. A simulacao deve considerar que a corrida  e em um velodromo com d metros e que n ciclistas comecam a prova em cada equipe (d > 249 e n > 4). A qualquer momento, com excec¸ao do instante da largada, no maximo, apenas 2 ciclistas podem estar lado a lado em cada ponto da pista, independente das suas equipes. Considere que cada ciclista ocupa exatamente 1 metro da pista e que a quantidade de ciclistas de cada equipe e no maximo ⌈d/4⌉. A quantidade de voltas sera sempre 16 independente do tamanho do velodromo. 

### 2 Requisitos
 
Seu simulador deve criar 2 × n threads “ciclista”. Seu codigo tera duas opcoes de execucao. Na primeira opcao todos os ciclistas conseguem pedalar exatamente na mesma  velocidade de 60Km/h (1m a cada 60ms) durante toda a prova. Na segunda opcao, todos os ciclistas fazem a primeira volta a 30Km/h mas a partir da segunda volta cada um dos ciclistas define suas velocidades aleatoriamente, para realizar a volta seguinte, como sendo 30 ou 60Km/h, com 50% de chance de escolher 60Km/h e 50% de chance de escolher 30Km/h. Se a velocidade sorteada para um ciclista for de 30Km/h, todos os ciclistas companheiros de equipe que estiverem atras dele, naquela volta, devem pedalar a 30Km/h, independente do valor que foi sorteado para eles. Desconsidere a acelerac¸ao necessaria para mudar a velocidade. Na volta seguinte, se o ciclista lento continuar lento, ele pode ser ultrapassado pelos seus companheiros de equipe caso haja algum ciclista atras dele com velocidade de 60Km/h. 

Seu codigo deve possuir um vetor compartilhado “pista” que tem um tamanho igual a d. Cada posicao do vetor corresponde portanto a 1 metro da pista. Em um dado instante de tempo, a posicao i da pista deve possuir os identificadores de todos os ciclistas que estao naquele trecho. A simulacao do seu codigo deve simular a corrida em intervalos de 60ms. Cada thread ciclista tem a obrigacao de escrever seu identificador na posicao correta do vetor pista a cada momento em que ele entra em um novo trecho de 1m, e de remover seu identificador da posicao referente ao trecho que ele acabou de sair. Como e possıvel perceber, cada posicao do vetor corresponde a uma variavel compartilhada que deve ter seu acesso controlado. Note que apesar de ter sorteado a velocidade de 60Km/h para a proxima volta, pode ser que um ciclista nao consiga de fato pedalar a essa velocidade, por exemplo, caso hajam 2 ciclistas na frente dele pedalando a 30Km/h.

Assim como no mundo real, ciclistas podem “quebrar” durante a prova e desistirem. Considere que a cada 4 voltas, ha a chance de 10% de que um ciclista quebre. Qual ciclista, pode ser definido de forma aleatoria. Caso algum ciclista quebre, essa informacao deve ser exibida na tela no momento exato em que ele quebrou. A volta em que ele estava, a posicao em que ele estava nessa volta e o identificador dele deve ser informado. Entretanto, quando houverem apenas 3 ciclistas em uma equipe, a probabilidade de quebra para todos os ciclistas daquela equipe deixa de existir. 

Toda vez que um ciclista quebrar, a thread dele deve ser destruida.

A saıda do seu programa deve ser um relatorio informando a cada volta completada pelo terceiro ciclista de uma equipe, todos os 3 primeiros ciclistas daquela equipe, o numero da volta, e o instante de tempo que esse terceiro ciclista passou pela linha de chegada (considere que a simulac¸ao comeca no instante de tempo 0). Ao termino da corrida (depois que todos os ciclistas passarem pela linha de chegada), deve ser informada qual equipe chegou em primeiro e qual chegou em segundo, ou se houve empate. A ordem final de chegada de todos os ciclistas, considerando a ordenacao da sua equipe e o instante de tempo que cada ciclista cruzou a linha de chegada tambem deve ser impresso na saida. Ciclistas que quebrarem devem ser identificados como tendo quebrado e, ao inves de mostrar as suas posicoes, deve ser informada a volta em que eles quebraram. Seu programa deve ainda permitir uma opcao de debug que informa a cada 60ms o status de cada posicao da pista, ou seja, o identificador do(s) ciclista(s) naquela posicao ou a informacao de que nao ha nenhum ciclista ali.

Nao ha um formato padrao para a saida do seu programa. Basta que ela informe tudo que foi solicitado no paragrafo anterior.


Com relacao  a entrada, seu simulador deve receber como argumentos nesta ordem:

````shell
d n [v|u] 
`````

O v deve ser usado para definir simulacoes com velocidades aleatorias a cada volta. O  u deve ser usado para definir simulac¸oes com velocidades uniformes de 60Km/h. Nao ha necessidade de validar a entrada. Lembre que seu programa e um simulador. Ou seja, a simulacao nao precisa levar o mesmo tempo que uma corrida de verdade levaria.
