#include <math.h>

// n!
int factorial(int n)
{
    return n<=1?1:n*factorial(n-1);
}

// nPk
int pick(int n, int k)
{
    return factorial(n)/factorial(n-k);
}

//nCk
int choose(int n, int k)
{
    return (n<k)?0:factorial(n)/(factorial(n-k)*factorial(k));
}

