#include <iostream>

int main() {
    long long n;
    std::cin >> n;

    n--;
    for (long long i = 1; i <= n; i++)
        n -= i;

    std::cout << n+1 << std::endl;
    return 0;
}


