#include <iostream>
#include "BST.hpp"
#include "list.hpp"

using namespace std;

void caracol(int matriz[n][n],int &rango){
    int i, j, k;
    for (k = 0; k < ((rango % 2) ? (rango / 2) + 1 : rango / 2); k++)
    {
    	for (i = j = k; j < (rango - k); ++j)
    		printf("%d ", matriz[i][j]);
        printf("\n");
    	for (--j, ++i; i < (rango - k); ++i)
    		printf("%d ", matriz[i][j]);
        printf("\n");
    	for (--i, --j; j >= k; --j)
    		printf("%d ", matriz[i][j]);
        printf("\n");
    	for (++j, --i; i > k; --i)
    		printf("%d ", matriz[i][j]);
    printf("\n");
	}
}

int main()
{
    int mat[2][2] = {{1,2},{3,4}};
    caracol(mat,2);
	return 0;
}
//--std=c++11^C
