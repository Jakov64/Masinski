#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Unesite n:\n");
    int n;  // definisemo promenljivu n
    scanf("%d",&n); //korisnik unosi vrednost n
    double mat[n][n]; // definisemo matricu dimenzija nxn, ciji su elementi realni brojevi

    printf("Unesite matricu:\n");
    for(int i = 0; i < n; i++){ // spoljasnja for petlja uvecava nas indeks i koji koristimo za prolaz kroz redove matrice
        for(int j = 0; j < n; j++){ // unutrasnja for petlja uvecava indeks j koji koristimo za prolazak kroz kolone matrice
            scanf("%lf", &mat[i][j]);   // korisnik unosi element matrice na poziciji (i,j)
        }
    }

    printf("DET: %lf\n", determinanta(n, mat));

    printf("Ispis matrice:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%.2lf ", mat[i][j]);    // ispisujemo korisniku na konzolu elemente matrice sa prve 2 decimale, red po red;
        }
        printf("\n");   // posle svakog ispisanog reda prelazimo u novi red na ispisu da bi bilo preglednije
    }

    return 0;
}
