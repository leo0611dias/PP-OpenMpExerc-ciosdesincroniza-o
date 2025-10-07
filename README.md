🧩 PP - OpenMP: Exercícios de Sincronização

Este projeto contém 5 exercícios práticos sobre sincronização em OpenMP (C++), cada um ilustrando um mecanismo diferente de controle de concorrência.
O objetivo é compreender como evitar condições de corrida e garantir resultados corretos em programas paralelos.

⚙️ Compilação e Execução

Todos os exercícios foram escritos em C++ com OpenMP.
Para compilar e executar qualquer um deles no terminal (Linux, macOS ou WSL) (gostaria de ressaltar que fiz em um sistema operacional linux), use:

g++ -fopenmp questaoN_nome.cpp -o questaoN_nome
./questaoN_nome

🔄 Substitua questaoN_nome.cpp pelo arquivo desejado, por exemplo:
questao1_critical.cpp, questao2_atomic.cpp, questao3_barrier.cpp, questao4_ordered.cpp, questao5_lock.cpp.

Resumo teórico uma demonstração mais "intuitiva":
| Diretiva   | Tipo de Sincronização  | Uso Principal                     | Nível de Controle  |
| ---------- | ---------------------- | --------------------------------- | ------------------ |
| `critical` | Exclusão mútua global  | Proteger blocos maiores de código | Médio              |
| `atomic`   | Exclusão mútua leve    | Atualizações simples em variáveis | Alto desempenho    |
| `barrier`  | Sincronização coletiva | Esperar todas as threads          | Controle de fase   |
| `ordered`  | Execução ordenada      | Manter ordem em seções paralelas  | Sequencial parcial |
| `locks`    | Exclusão mútua manual  | Controle granular e dinâmico      | Avançado           |


🧠 Abaixo fiz uma breve explicação dos Exercícios
Exercício 1 – Critical

Objetivo: Somar as raízes de N equações em paralelo usando uma região crítica.
Cada thread acumula um subtotal local e, ao final, entra numa seção #pragma omp critical para atualizar a variável compartilhada soma_total.
Isso impede condições de corrida e assegura a integridade do resultado final.
➡️ Resultado esperado: N * 5.0

Exercício 2 – Atômico

Objetivo: Demonstrar a atualização atômica de variáveis compartilhadas.
O código paraleliza o loop e utiliza #pragma omp atomic para somar valores de forma eficiente.
A diretiva atomic é mais leve que critical para operações simples (como adições), evitando bloqueios complexos e aumentando o desempenho.

Exercício 3 – Barrier

Objetivo: Aplicar uma barreira de sincronização explícita com #pragma omp barrier.
Cada thread calcula e armazena seu subtotal em soma_por_thread[tid].
Após a barreira, apenas uma thread realiza a soma final.
Esse padrão é útil quando é necessário aguardar todas as threads antes de iniciar uma nova etapa do algoritmo.

Exercício 4 – Ordered

Objetivo: Manter a ordem de execução controlada mesmo com paralelismo.
Dentro do loop paralelo, uma região #pragma omp ordered garante que as impressões (cout) ocorram na ordem crescente de i.
Assim, o programa continua paralelo, mas preserva a sequência lógica de saída.

Exercício 5 – Locks

Objetivo: Usar travas explícitas (locks) para proteger regiões críticas.
Em vez de critical ou atomic, o código utiliza omp_set_lock() e omp_unset_lock() para controlar o acesso à variável soma_total.
Locks oferecem maior controle e permitem manipulações mais finas (como tentativas de aquisição), mas exigem cuidado para evitar deadlocks.
