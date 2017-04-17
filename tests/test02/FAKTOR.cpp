#include <iostream>

const int fin = 10000;
int a[fin+1];

int main()
{ 
    int n;
    std::cin >> n;
    for(int i = 2; i <= n; i++) {
        int cinilac = i;
        int pfaktor = 2;
        while(cinilac > 1)
        {
            while(cinilac % pfaktor == 0) {
                cinilac /= pfaktor;
                a[pfaktor]++;
            }
            pfaktor++;
        }
    }
    int br = 0;
    for(int i = 1;i <= fin; i++)
        br += a[i];
    std::cout << br << std::endl;
    return 0;
}

