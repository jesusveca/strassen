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

void suma_matriz(double A[][SZ], double B[][SZ], double resultado[][SZ], int n) {
    int i, j;
    for(i=0; i< n; i++) {
        for(j=0; j<n; j++)  resultado[i][j] = A[i][j] + B[i][j];
    }
}

void resta_matriz(double A[][SZ], double B[][SZ], double resultado[][SZ], int n) {
    int i, j;
    for(i=0; i< n; i++) {
        for(j=0; j<n; j++)  resultado[i][j] = A[i][j] - B[i][j];
    }
}

void strassen(double A[][SZ], double B[][SZ], double C[][SZ], int n) {

    if(n== 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    else{
        int divide_  =(n/2),i,j;
        double A11[SZ][SZ], A12[SZ][SZ], A21[SZ][SZ], A22[SZ][SZ],B11[SZ][SZ], B12[SZ][SZ], B21[SZ][SZ], B22[SZ][SZ], C11[SZ][SZ], C12[SZ][SZ], C21[SZ][SZ], C22[SZ][SZ];
        double P1[SZ][SZ], P2[SZ][SZ], P3[SZ][SZ], P4[SZ][SZ], P5[SZ][SZ], P6[SZ][SZ], P7[SZ][SZ];
        double AResultado[SZ][SZ], BResultado[SZ][SZ];
        
        for (i = 0; i < divide_; i++)        {
            for (j = 0; j < divide_; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + divide_];
                A21[i][j] = A[i + divide_][j];
                A22[i][j] = A[i + divide_][j + divide_];
                
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + divide_];
                B21[i][j] = B[i + divide_][j];
                B22[i][j] = B[i + divide_][j + divide_];
            }
        }
        
        // calculando p1 hasta p7
        suma_matriz(A11, A22, AResultado, divide_);   // a11 + a22
        suma_matriz(B11, B22, BResultado, divide_);   // b11 + b22
        strassen(AResultado, BResultado, P1, divide_);  // p1 = (a11+a22) * (b11+b22)
        
        suma_matriz(A21, A22, AResultado, divide_);   // a21 + a22
        strassen(AResultado, B11, P2, divide_); // p2 = (a21+a22) * (b11)
        
        resta_matriz(B12, B22, BResultado, divide_); // b12 - b22
        strassen(A11, BResultado, P3, divide_); // p3 = (a11) * (b12 - b22)
        
        resta_matriz(B21, B11, BResultado, divide_); // b21 - b11
        strassen(A22, BResultado, P4, divide_); // p4 = (a22) * (b21 - b11)
        
        suma_matriz(A11, A12, AResultado, divide_); // a11 + a12
        strassen(AResultado, B22, P5, divide_); // p5 = (a11+a12) * (b22)
        
        resta_matriz(A21, A11, AResultado, divide_); // a21 - a11
        suma_matriz(B11, B12, BResultado, divide_); // b11 + b12
        strassen(AResultado, BResultado, P6, divide_); // p6 = (a21-a11) * (b11+b12)
        
        resta_matriz(A12, A22, AResultado, divide_); // a12 - a22
        suma_matriz(B21, B22, BResultado, divide_); // b21 + b22
        strassen(AResultado, BResultado, P7, divide_); // p7 = (a12-a22) * (b21+b22)
        
        // calculando c21, c21, c11 e c22:
        
        suma_matriz(P3, P5, C12, divide_); // c12 = p3 + p5
        suma_matriz(P2, P4, C21, divide_); // c21 = p2 + p4
        
        suma_matriz(P1, P4, AResultado, divide_); // p1 + p4
        suma_matriz(AResultado, P7, BResultado, divide_); // p1 + p4 + p7
        resta_matriz(BResultado, P5, C11, divide_); // c11 = p1 + p4 - p5 + p7
        
        suma_matriz(P1, P3, AResultado, divide_); // p1 + p3
        suma_matriz(AResultado, P6, BResultado, divide_); // p1 + p3 + p6
        resta_matriz(BResultado, P2, C22, divide_); // c22 = p1 + p3 - p2 + p6

        // agrupando los resultados obtenidos en una matriz
        for (i = 0; i < divide_ ; i++)   {
            for (j = 0 ; j < divide_ ; j++)  {
                C[i][j] = C11[i][j];
                C[i][j + divide_] = C12[i][j];
                C[i + divide_][j] = C21[i][j];
                C[i + divide_][j + divide_] = C22[i][j];
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
    strassen(A,B,C,n);
    
    cout<<"Matriz A : \n---------\n";                  imprimir(A,m);
    cout<<"\nMatriz B : \n---------\n";                imprimir(B,m);
    cout<<"\nLa matriz producto C  : \n--------------\n";   imprimir(C,m);
    cout<<"\n \n";
    return 0;
}