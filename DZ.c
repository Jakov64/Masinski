#include <stdio.h>
#include <stdlib.h>

double determinanta(int n, double mat[n][n]) {
    if(n == 1){ // ako postoji samo jedan element u matrici onda je taj element determinanta, bazni slucaj rekurzije
        return mat[0][0];   // vracamo taj element
    }
    if(n == 2){ // znamo kako da izracunamo determinantu matrice dimenzije 2x2, jos jedan bazni slucaj
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }

    double rezultat = 0; // ovde sabiramo clanove laplasovog razvoja
    double minor[n-1][n-1]; //pravimo pomocnu minor matricu, izbacujemo prvi red i jednu kolonu (izbacena kolona zavisi od trenutnog clana)

    // ubacujemo elemente u minor matricu
    for(int kolona = 0; kolona < n; kolona++){  // prolazimo kroz sve kolone prvog reda nase originalne matrice. Svaka kolona daje jedan clan laplasovog razvoja
        for(int i = 1; i < n; i++){ // ova petlja prolazi kroz redove matrice polazeci od drugog reda jer prvi izbacujemo
            int kolonaMinora = 0;   // oznacava u koju kolonu minora upisujemo elemnt, posto izbacujemo trenutnu kolonu iz originalne matrice kada pravimo minor

            for(int j = 0; j < n; j++){ // prolazimo kroz kolone trenutnog reda
                if(j != kolona){    // upisujemo sve kolone u minor sem kolone koja je trenutno izabrana u originalnoj matrici
                    minor[i-1][kolonaMinora] = mat[i][j];   //upisujemo element u minor, red u minoru je za jedan manji od reda u matrici
                    kolonaMinora++; // prelazimo na sledecu kolonu minora
                }
            }
        }
        if(kolona%2 == 0){  // ako je broj kolone paran predznak je plus. Uslov: (-1)^(i+j), moze da se napise ovako jer uvek gledamo prvi red, pa nam broj reda ne utice na uslov
            rezultat += mat[0][kolona] * determinanta(n-1, minor);  // mnozimo izabrani element u matrici sa odgovarajucim minorom koji izracunavamo rekurzivno
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

    double det = determinanta(n,mat);   // izracunavamo determinantu
    printf("DET: %lf\n", det);

    if(det != 0){   // inverzna matrica postoji ako je determinanta razlicita od 0
        // sad pravimo inverznu matricu A^(-1)= 1/(det(A))*adj(A) (prvo moramo da nadjemo adjungovanu matricu)
        // adj(A) tako sto prvo napravimo matricu kofaktora i onda je transponujemo (to radimo u jendom koraku jer odmah kofaktore upisujemo na transponovane pozicije)

        double adj[n][n];  // definisemo adjungovanu matricu

        for(int i = 0; i < n;i++){  // prolazimo kroz sve elemente originalne matrice, fiksiramo element mat[i][j] i pravimo njegovu minor matricu
            for(int j = 0; j < n;j++){
                double minorElementa[n-1][n-1]; // pravimo pomocnu minor matricu trenutnog elementa kako bismo izracunali njegov kofaktor
                int redMinora = 0;  // prati u koji red minora upisujemo

                for(int r = 0; r < n; r++){
                    if(r != i){ // upisujemo sve redove osim i-tog reda
                        int kolonaMinora = 0; //prati u koju kolonu minora upisujemo

                        for(int k = 0; k < n; k++){
                            if(k != j){ // upisujemo sve kolone osim j-te kolone
                                minorElementa[redMinora][kolonaMinora] = mat[r][k]; // upisujemo element u minor
                                kolonaMinora++; // idemo na sledecu kolonu
                            }
                        }
                        redMinora++;    // idemo na sledeci red
                    }
                }
                if((i+j)%2 == 0){   // odredjujemo predznak kofaktora (minora sa predznakom)
                    adj[j][i] = determinanta((n-1), minorElementa); // izracunavamo determinantu nase pomocne minor matrice(racunamo minor elementa)
                }else{
                    adj[j][i] = -determinanta((n-1), minorElementa);    // kofaktore odmah ubacujemo na transponovane pozicije i tako odmah dobijamo adjungovanu matricu
                }
            }
        }

        double inverznaMat[n][n];
        double k = 1/det;   // inicijalizujemo k radi lepseg zapisa
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n;j++){
                inverznaMat[i][j] = k * adj[i][j];  // posto je 1/det(A) realna broj, mnozimo svaki element matrice sa tim brojem
            }
        }

        printf("Ispis izverzne matrice:\n");
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                printf("%.2lf ", inverznaMat[i][j]);    // ispisujemo korisniku na konzolu elemente matrice sa prve 2 decimale, red po red;
            }
            printf("\n");
        }
    }

    printf("Ispis matrice:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%.2lf ", mat[i][j]);    // ispisujemo korisniku na konzolu elemente matrice sa prve 2 decimale, red po red;
        }
        printf("\n");   // posle svakog ispisanog reda prelazimo u novi red na ispisu da bi bilo preglednije
    }

    return 0;
}
