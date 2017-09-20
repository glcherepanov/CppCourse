#include <cstdio>
#include <cmath>

int main()

{
    std::puts("Please enter a, b and c for 'ax^2 + bx + c = 0':");

    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);

    float d = pow(b, 2) - 4 * a * c;
    float x1 = ((-1) * b - sqrt(d)) / (2 * a);
    float x2 = ((-1) * b + sqrt(d)) / (2 * a);
    std::printf("solution: %f %f\n", x1, x2);
}