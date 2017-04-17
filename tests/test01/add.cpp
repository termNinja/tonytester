/*
 * add.cpp
 * Copyright (C) 2017 Nemanja Micovic <nmicovic@outlook.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>

int add(int x, int y) {
    return x + y;
}

int main()
{
    int x, y;
    std::cin >> x >> y;
    int t = add(x, y);
    std::cout << t;
    return 0;
}
