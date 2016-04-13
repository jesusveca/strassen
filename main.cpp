#include <iostream>
#include <math.h>
#include <vector>

#define SZ 8

using namespace std;

void imprimir(double A[][SZ], int n) {
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++)  cout<<A[i][j]<<" ";
        cout<<"\n";
    }
}

void suma_matriz(double A[][SZ], double B[][SZ], double Result[][SZ], int n) {
    int i, j;
    for(i=0; i< n; i++) {
        for(j=0; j<n; j++)  Result[i][j] = A[i][j] + B[i][j];
    }
}

void resta_matriz(double A[][SZ], double B[][SZ], double Result[][SZ], int n) {
    int i, j;
    for(i=0; i< n; i++) {
        for(j=0; j<n; j++)  Result[i][j] = A[i][j] - B[i][j];
    }
}

void StrassenAlgorithm(double A[][SZ], double B[][SZ], double C[][SZ], int n) { //Strassen, dividir y conquistar

    if(n== 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    else{
        int Divide  =(n/2),i,j;
        double A11[SZ][SZ], A12[SZ][SZ], A21[SZ][SZ], A22[SZ][SZ],B11[SZ][SZ], B12[SZ][SZ], B21[SZ][SZ], B22[SZ][SZ], C11[SZ][SZ], C12[SZ][SZ], C21[SZ][SZ], C22[SZ][SZ];
        double P1[SZ][SZ], P2[SZ][SZ], P3[SZ][SZ], P4[SZ][SZ], P5[SZ][SZ], P6[SZ][SZ], P7[SZ][SZ];
        double AResult[SZ][SZ], BResult[SZ][SZ];
        
        for (i = 0; i < Divide; i++)        {
            for (j = 0; j < Divide; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + Divide];
                A21[i][j] = A[i + Divide][j];
                A22[i][j] = A[i + Divide][j + Divide];
                
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + Divide];
                B21[i][j] = B[i + Divide][j];
                B22[i][j] = B[i + Divide][j + Divide];
            }
        }
        
        // calculando p1 hasta p7
        suma_matriz(A11, A22, AResult, Divide);   // a11 + a22
        suma_matriz(B11, B22, BResult, Divide);   // b11 + b22
        StrassenAlgorithm(AResult, BResult, P1, Divide);  // p1 = (a11+a22) * (b11+b22)
        
        suma_matriz(A21, A22, AResult, Divide);   // a21 + a22
        StrassenAlgorithm(AResult, B11, P2, Divide); // p2 = (a21+a22) * (b11)
        
        resta_matriz(B12, B22, BResult, Divide); // b12 - b22
        StrassenAlgorithm(A11, BResult, P3, Divide); // p3 = (a11) * (b12 - b22)
        
        resta_matriz(B21, B11, BResult, Divide); // b21 - b11
        StrassenAlgorithm(A22, BResult, P4, Divide); // p4 = (a22) * (b21 - b11)
        
        suma_matriz(A11, A12, AResult, Divide); // a11 + a12
        StrassenAlgorithm(AResult, B22, P5, Divide); // p5 = (a11+a12) * (b22)
        
        resta_matriz(A21, A11, AResult, Divide); // a21 - a11
        suma_matriz(B11, B12, BResult, Divide); // b11 + b12
        StrassenAlgorithm(AResult, BResult, P6, Divide); // p6 = (a21-a11) * (b11+b12)
        
        resta_matriz(A12, A22, AResult, Divide); // a12 - a22
        suma_matriz(B21, B22, BResult, Divide); // b21 + b22
        StrassenAlgorithm(AResult, BResult, P7, Divide); // p7 = (a12-a22) * (b21+b22)
        
        // calculando c21, c21, c11 e c22:
        
        suma_matriz(P3, P5, C12, Divide); // c12 = p3 + p5
        suma_matriz(P2, P4, C21, Divide); // c21 = p2 + p4
        
        suma_matriz(P1, P4, AResult, Divide); // p1 + p4
        suma_matriz(AResult, P7, BResult, Divide); // p1 + p4 + p7
        resta_matriz(BResult, P5, C11, Divide); // c11 = p1 + p4 - p5 + p7
        
        suma_matriz(P1, P3, AResult, Divide); // p1 + p3
        suma_matriz(AResult, P6, BResult, Divide); // p1 + p3 + p6
        resta_matriz(BResult, P2, C22, Divide); // c22 = p1 + p3 - p2 + p6

        // agrupando los resultados obtenidos en una matriz
        for (i = 0; i < Divide ; i++)   {
            for (j = 0 ; j < Divide ; j++)  {
                C[i][j] = C11[i][j];
                C[i][j + Divide] = C12[i][j];
                C[i + Divide][j] = C21[i][j];
                C[i + Divide][j + Divide] = C22[i][j];
            }
        }
    }
}

int main() {
    double C[SZ][SZ];
    int i,j;
    int n,m,cont = 0;
    n=5; m = n;
    double A[SZ][SZ] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5},{1, 2, 3, 4, 5},{1, 2, 3, 4, 5}};
    double B[SZ][SZ] = {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1},{1, 1, 1, 1, 1},{1, 1, 1, 1, 1}};
    
    //rellena con 0.0 lo restante del SZ, como un fill() pero solo los espacios no tomados de 'n' para que complete SZ
    if(m > 1) {
        while(m>=2) {
            m/=2;
            cont++;
        }
        m = n;
        if(m != (pow(2.0,cont))) {
            n = pow(2.0,cont+1);
            for(i=0; i<n; i++)  {
                for(j=0; j<n; j++)  {
                    if((i>=m) || (j>=m))    {
                        A[i][j] = 0.0;
                        B[i][j] = 0.0;
        }}}}}
    StrassenAlgorithm(A,B,C,n);
    
    cout<<"Matriz A : \n---------\n";                  imprimir(A,m);
    cout<<"\nMatriz B : \n---------\n";                imprimir(B,m);
    cout<<"\nLa matriz producto C  : \n--------------\n";   imprimir(C,m);
    cout<<"\n \n";
    return 0;
}