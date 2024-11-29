# Projeto2_EDL
O projeto utiliza tabela hashing para simular um sistema de baús em jogos. Nesse caso cada item tem seu nome próprio, e sua própria quantidade. Porém, cada item tem um limite de 64 unidades por posição na tabela. O projeto também conta com o enderaçamento aberto e fechado, metódos diferentes de hashing que podem alterar o desempenho em algumas funções. 

# Endereçamento Fechado:
- Quando uma colisão ocorrer, os elementos que colidirem devem ser armazenados em uma lista encadeada (no caso, simplemente encadeada) na posição correspondente da tabela.

# Endereçamento Aberto:
- Quando uma colisão ocorrer, a tabela deve procurar uma nova posição para armazenar o elemento utilizando alguma técnica de sondagem, como sondagem linear, sondagem quadrática, etc. Nesse caso, foi utilizado a sondagem linear.
