// UM BREVE RESUMO: usar #pragma omp critical para atualizar soma global
//Objetivo: somar todas as raízes em paralelo sem perda de atualizações.
//Etapas: cada thread calcula uma soma_local em seu bloco de iterações.
//depois entra numa seção crítica (#pragma omp critical) para somar soma_local à soma_total. A seção crítica evita corrida de dados.
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
    double soma_total = 0.0;

    #pragma omp parallel
    {
        double soma_local = 0.0;
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            auto r = resolver_bhaskara(a[i], b[i], c[i]);
            soma_local += r.first + r.second;
        }
        // seção crítica para agregar à soma global
        #pragma omp critical
        {
            soma_total += soma_local;
        }
    }

    std::cout << "Soma total (critical): " << soma_total << "\n";
    std::cout << "Esperado: " << N * 5.0 << "\n";
    return 0;
}
