#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    int tam_vetor = 1000000;
    int* random_ints = (int*)malloc(tam_vetor*sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < tam_vetor; ++i) {
        random_ints[i] = rand() % 100;
    }
    
    int variavel = 10; 
    int total_ocorrencias = 0;
    int valor_total = 0; 

    #pragma omp parallel num_threads(4)

    {
        #pragma omp for reduction (+: total_ocorrencias)
            for (int i = 0; i < tam_vetor; i++)
            {
                if (random_ints[i] == variavel)
                {
                    total_ocorrencias ++;
                } 
            }
    }

    #pragma omp parallel num_threads(4)

    {
        #pragma omp for reduction (+: valor_total)
            for (int i = 0; i < tam_vetor; i++)
            {
                valor_total += random_ints[i]; 
            }
    }

    float media = valor_total/tam_vetor;

    printf("Total ocorrencias de %d: %d", variavel, total_ocorrencias);
    printf("\nMedia do vetor: %f", media);
    return 0;
}

