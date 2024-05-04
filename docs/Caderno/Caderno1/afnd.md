
# Autômoto Finito e Não Determinístico 

- A máquina agora pode estar com vários estados ativos ao mesmo tempo.

- Agora podemos ter uma transição épsilon. Ou seja, **podemos mudar de estado sem ler algo.**


- Muito similar ao conceito de threads.


- Todo AFN tem um AFD equivalente se K é o número de estados do AFN, ele tem 2^k subconjuntos de estados. Por exemplo, Se ele possui 4 estados em AFN, quando ele passar parar AFD terá 16 estados.


- **Podemos ir para mais de um estado consumindo um mesmo simbolo**. Quando há essa possibilidade "cria-se uma cópia" da máquina para cada uma. Quando não há, a máquina desaparece. Isso ocorre pela possibilidade de podermos ficar ou não em um estado dado a leitura de um mesmo simbolo (podemos explorar mais caminhos)


- **Qualquer autômato finito não determinístico pode se tornar determinístico.** 




