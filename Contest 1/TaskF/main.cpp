// TaskFC++.cpp
#include <iostream>
#include <cmath>
#include <string>

double pi = 3.14159265;

void sinFind(double angle, double epsilon)
{
    int new_angle = angle >= -pi / 2 ? 1 : -1;
    double new_sin = 1;
    double old_sin = 0;
    int e = 0;
    int factorial = 1;
    while (!(angle <= pi / 2 && angle >= -pi / 2))
    {
        new_angle = angle < -pi / 2 ? -1 : 1;
        angle = angle <= pi / 2 ? angle + pi : pi - angle;
    }
    for (; std::abs(new_sin - old_sin) > epsilon; ++e)
    {
        new_sin = old_sin;
        old_sin += (e % 2 != 1 ? 1 : -1) * pow(angle, 2 * e + 1) / factorial;

        if (epsilon > std::abs(new_sin - old_sin) & 0 < e)
        {
            break;
        }
        factorial *= (2 * e + 2) * (2 * e + 3);
    }
    std::cout << std::round(new_sin * new_angle / epsilon) * epsilon << "\n";
    std::cout << std::to_string(e);
}

int main()
{
    double angle;
    double eps;
    std::cin >> angle;
    std::cin >> eps;
    int n = static_cast<int>(angle / (2 * pi));
    angle -= 2 * pi * n;
    sinFind(angle, eps);
    return 0;
}
