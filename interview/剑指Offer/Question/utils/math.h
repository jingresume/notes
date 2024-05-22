#ifndef __QUESTION_UTILS_MATH_H
#define __QUESTION_UTILS_MATH_H

long long binPow(long long a, long long b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}


#endif