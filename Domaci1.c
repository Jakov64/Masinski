#include <stdio.h>
#include <stdlib.h>

double determinanta(int n, double mat[n][n]) {
    if(n == 1){ // ako postoji samo jedan element u matrici onda je taj element determinanta
        return mat[0][0];
    }

    double rezultat = 0; // ovde sabiramo clanove laplasovog razvoja
    double minor[n-1][n-1]; //pravimo pomocnu minor matricu, izbacujemo prvi red i jednu kolonu

    // ubacujemo elemente u minor matricu
    for(int kolona = 0; kolona < n; kolona++){  // prolazimo kroz sve kolone prvog reda i svaka kolona daje jedan clan laplasovog razvoja
        for(int i = 1; i < n; i++){ // ova petlja prolazi kroz redove matrice polazeci od drugog reda jer prvi izbacujemo
            int kolonaMinora = 0;   // u koju kolonu minora upisujemo element

            for(int j = 0; j < n; j++){ // prolazimo kroz kolone trenutnog reda
                if(j != kolona){
                    minor[i-1][kolonaMinora] = mat[i][j];   //upisujemo element u minor, red u minoru je za jedan manji od reda u matrici
                    kolonaMinora++; // prelazimo na sledecu kolonu minora
                }
            }
        }
        if(kolona%2 == 0){  // ako je broj kolone paran predznak je plus
            rezultat += mat[0][kolona] * determinanta(n-1, minor);
        }else{  // ako je broj kolone neparan predznak je minus
            rezultat -= mat[0][kolona] * determinanta(n-1, minor);
        }
    }

    return rezultat; // vracamo determinantu
}

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
