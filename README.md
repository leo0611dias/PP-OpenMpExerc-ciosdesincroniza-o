Como compilar?
g++ -fopenmp exN.cpp -o exN
./exN
(Substitua exN.cpp por cada arquivo, por exemplo questão1_critical.cpp, )# PP-OpenMpExerc-ciosdesincroniza-o


Explicações das 5 questões

Exercício 1 (critical)
Objetivo: somar todas as raízes de N equações em paralelo usando uma seção crítica. O código paraleliza o for com OpenMP; cada thread acumula localmente e, ao final, entra numa região #pragma omp critical para adicionar seu subtotal à soma_total. A seção crítica previne condições de corrida garantindo integridade do resultado. Resultado esperado: N * 5.0.

Exercício 2 (atomic)
Objetivo: demonstrar atualização atômica em variáveis compartilhadas. Cada iteração calcula as raízes e atualiza soma_total com #pragma omp atomic. A operação atomic é mais eficiente que critical para operações simples (como soma), evitando bloqueios mais pesados e reduzindo contenção.

Exercício 3 (barrier)
Objetivo: usar sincronização explícita com #pragma omp barrier e fazer uma redução manual. Cada thread escreve sua soma em um slot soma_por_thread[tid]. Depois de barrier (que espera todas completarem), um único thread faz a agregação. Esse padrão é útil quando você precisa de um ponto de sincronização antes de executar uma fase subsequente.

Exercício 4 (ordered)
Objetivo: garantir que efeitos colaterais (impressão) ocorram na ordem lógica dos índices. O loop é paralelizado, mas a região #pragma omp ordered dentro do corpo garante que as linhas cout saiam na ordem crescente de i. Útil quando a ordem de saída importa, mas ainda queremos paralelizar o processamento.

Exercício 5 (locks)
Objetivo: demonstrar uso de locks OpenMP (omp_lock_t) para proteger seções críticas. Em vez de critical ou atomic, o código usa omp_set_lock/omp_unset_lock para proteger soma_total. Locks dão mais controle (ex.: testes, tentativa de aquisição) mas exigem cuidado para evitar deadlocks.
