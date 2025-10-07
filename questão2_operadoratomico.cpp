//Resumo: usar #pragma omp atomic para somar
//Objetivo: evitar corrida de dados com menor overhead que critical.
//Etapas: cada iteração soma diretamente ao soma_total usando #pragma omp atomic, que garante a operação de leitura-modifica-escreve como atômica.
Etapas: cada iteração soma diretamente ao soma_total usando #pragma omp atomic, que garante a operação de leitura-modifica-escreve como atômica.
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

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        auto r = resolver_bhaskara(a[i], b[i], c[i]);
        // atualização atômica 
        #pragma omp atomic
        soma_total += r.first + r.second;
    }

    std::cout << "Soma total (atomic): " << soma_total << "\n";
    std::cout << "Esperado: " << N * 5.0 << "\n";
    return 0;
}
