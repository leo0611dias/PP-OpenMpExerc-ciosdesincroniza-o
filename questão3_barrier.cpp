//Resumo:
//Objetivo: demonstrar sincronização explícita com barrier e redução manual.
//Etapas: cada thread armazena sua soma em soma_por_thread[tid]; 
//#pragma omp barrier garante que todas completaram antes de um único thread agregar (em #pragma omp single) os resultados.
// ex3_barrier.cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

std::pair<double,double> resolver_bhaskara(double a, double b, double c) {
    double delta = b*b - 4*a*c;
    if (delta < 0) return {0.0, 0.0};
    double x1 = (-b + std::sqrt(delta)) / (2*a);
    double x2 = (-b - std::sqrt(delta)) / (2*a);
    return {x1, x2};
}

int main() {
    const int N = 1000;
    std::vector<double> a(N,1.0), b(N,-5.0), c(N,6.0);

    int nthreads = omp_get_max_threads();
    std::vector<double> soma_por_thread(nthreads, 0.0);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            auto r = resolver_bhaskara(a[i], b[i], c[i]);
            soma_por_thread[tid] += r.first + r.second;
        }

        // garante que todas as threads terminaram suas somas locais antes da redução
        #pragma omp barrier

        #pragma omp single
        {
            double soma_total = 0.0;
            for (double v : soma_por_thread) soma_total += v;
            std::cout << "Soma total (barrier + reduction manual): " << soma_total << "\n";
            std::cout << "Esperado: " << N * 5.0 << "\n";
        }
    }

    return 0;
}
