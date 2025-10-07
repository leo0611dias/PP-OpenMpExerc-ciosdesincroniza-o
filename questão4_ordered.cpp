//resumo: usar #pragma omp ordered para manter ordem ao imprimir resultado
//Objetivo: quando precisamos que certos efeitos colaterais (ex.: cout) respeitem a ordem de índices.
//Etapas: #pragma omp parallel for ordered e dentro do loop #pragma omp ordered garantem que a impressão será feita na ordem crescente de i 
//mesmo com execução paralela. Usei N=20 para saída legível.

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
    const int N = 20; // reduzido para não inundar a saída
    std::vector<double> a(N,1.0), b(N,-5.0), c(N,6.0);
    double soma_total = 0.0;

    #pragma omp parallel for ordered reduction(+:soma_total)
    for (int i = 0; i < N; ++i) {
        auto r = resolver_bhaskara(a[i], b[i], c[i]);
        double s = r.first + r.second;
        soma_total += s;

        // imprime na ordem dos índices i (usando ordered)
        #pragma omp ordered
        {
            std::cout << "i=" << i << " -> roots: " << r.first << ", " << r.second << " sum=" << s << "\n";
        }
    }

    std::cout << "Soma total (ordered): " << soma_total << "\n";
    std::cout << "Esperado: " << N * 5.0 << "\n";
    return 0;
}
