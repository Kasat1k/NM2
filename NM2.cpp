
#include <iostream>
#include<cmath>
#include<cstdio>
#include <iomanip>
using namespace std;


double ab(int k) {
    double a = (1 +( 2.0 / k));
    return a;
}
double cb(int k) {
    double c = (7 - (1.0 / k));

    return c;
}



const int n =30;
int i, j, m, k;
double maxel, bb;
int main()

{
    setlocale(LC_ALL, "Russian");
    double matrix[n + 2][n + 2] = { 0 };
    double mnul[n + 2][n + 2] = { 0 };
    double B[n+1];
    double M[n + 1][n + 1];
    int j = 0;
    double r[n] = {0};
    matrix[n][1] = ab(30);
    for (int i = 1; i < n+1; i++) { matrix[1][i] = ab(i); mnul[1][i] = ab(i); }
    for (int i = 2; i < n+1; i++) { matrix[i][i] = cb(i); matrix[i][i - 1] = (-1)*cb(i-1); mnul[i][i] = cb(i); mnul[i][i - 1] = (-1) * cb(i - 1);}
    for (int i = 1; i < n + 1; i++) { matrix[i][n+1] = n - i + 2;  B[i]= n - i + 2;}
    double* x;
    x = (double*)malloc(n * sizeof(double));
    for (k = 1; k < n+1; k++) //Поиск максимального элемента в первом столбце
    {
        maxel = abs(matrix[k][k]);
        i = k;
        for (m = k + 1; m < n+1; m++)
            if (abs(matrix[m][k]) > maxel)
            {
                i = m;
                maxel = abs(matrix[m][k]);
            }

        if (maxel == 0)   //проверка на нулевой элемент
        {
            cout << "Система не имеет решений" << endl;
        }

        if (i != k)  //  перестановка i-ой строки, содержащей главный элемент k-ой строки
        {
            for (j = k; j < n + 2; j++)
            {
                bb = matrix[k][j];
                matrix[k][j] = matrix[i][j];
                matrix[i][j] = bb;
            }
        }
        maxel = matrix[k][k];//преобразование k-ой строки (Вычисление масштабирующих множителей)
        matrix[k][k] = 1;
        for (j = k + 1; j < n + 2; j++)
            matrix[k][j] = matrix[k][j] / maxel;
        for (i = k + 1; i < n+1; i++)//преобразование строк с помощью k-ой строки
        {
            bb = matrix[i][k];
            matrix[i][k] = 0;
            if (bb != 0)
                for (j = k + 1; j < n + 2; j++)
                    matrix[i][j] = matrix[i][j] - bb * matrix[k][j];
        }
    }
    x = (double*)malloc(n * sizeof(double));
    
    for (i = n ; i > 0; i--)   //Нахождение решений СЛАУ
    {
        x[i] = 0;
        maxel = matrix[i][n];
        for (j = n+1; j > i; j--)
            maxel = maxel - matrix[i][j] * x[j];
        x[i] = maxel;
    }

     cout << "Решение системы:" << endl; 
    for (i = 0; i < n; i++)
    {
        cout << "x[" << i + 1 << "]=" << x[i];
        cout << endl;
    } 
    for (i = 1; i <= n ; i++) 
    {
        for (j = 1; j <= n; j++)
        {
            r[i-1] = r[i - 1] + x[i-1]*mnul[i][j];
        }
    }
    for (j = 1; j <= n; j++)
    {
        r[j - 1] = B[j];
    }
}

