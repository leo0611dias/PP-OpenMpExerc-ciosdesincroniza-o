// resumo: usar omp_lock_t (locks) para proteger seção crítica
//Objetivo: proteger seção crítica usando lock explícito.
//Etapas: antes de atualizar soma_total chama-se omp_set_lock(&lock) e, após a atualização, omp_unset_lock(&lock). Lock é inicializado e destruído corretamente.
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <iomanip>


std::pair<double,double> resolver_bhaskara_lock(double a, double b, double c) {
double delta = b*b - 4*a*c;
if (delta < 0) return {0.0, 0.0};
double sqrt_delta = std::sqrt(delta);
return {(-b + sqrt_delta) / (2*a), (-b - sqrt_delta) / (2*a)};
}


int main_lock() {
const int N = 1000;
std::vector<double> a(N, 1.0), b(N, -5.0), c(N, 6.0);
double soma_total = 0.0;
  
omp_lock_t lock;
omp_init_lock(&lock);
#pragma omp parallel
{
#pragma omp for nowait
for (int i = 0; i < N; ++i) {
auto r = resolver_bhaskara_lock(a[i], b[i], c[i]);
double s = r.first + r.second;
omp_set_lock(&lock);
soma_total += s;
omp_unset_lock(&lock);
}
}

omp_destroy_lock(&lock);

std::cout << std::fixed << std::setprecision(2);
std::cout << "Soma total (lock): " << soma_total << "\n";
std::cout << "Esperado: " << N * 5.0 << "\n";
return 0;
}
