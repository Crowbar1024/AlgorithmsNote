#include <myheader.h>



// 69 easy 牛顿法找x的根t
// 假设f(x)=0，已知(x0,f(x0))是f(x)的点
// 那么经过(x0,f(x0))的切线就是 y = f(x0) + f'(x0)(x-x0)
// 所以x轴的交点就是(x0-f(x0)/f'(x0), 0)
// 然后迭代条件就是f(x)>0 (因为初始条件就是从>0的部分开始迭代的，所以初始如果从<0开始的话，需要相应的改变迭代条件)
// 这里就是求 t*t - x = 0 的t，所以初始的t要大
// 所以t = t - (f(t)/f(t)') = t - ((t*t-x) / (2t) = t/2 + x/(2t)
int mySqrt(int x) {
    // const double eps = 1e-6;
    long long t = x;
    while (x < t * t) {
        // t = t / 2 + x / (2 * t);  // 除法最好写在最后，不要拆开
        t = (t + x / t) / 2;
    }
    return t;
}
// 衍生：判断x是否是完全平方数 367

// 50 medium 求幂x^n
// 核心思想：快速幂
// 快速幂的本质：一个一个去乘太麻烦，把一共要乘的次数n用二进制的形式写出来，这个步骤复杂度是logn级别的
// 举个例子，求x^26，26的二进制是1 1 0 1 0。从最后一位开始创建
// 最后一位是0，写0，形式上就是res不变；
// 进位，体现为x=x*x，m/2=13；
// 13最后一位是1，那么在这个位置上写1，形式上就是res乘上x的这个位置的幂，以此类推……
// 难点：如果n是负数，那么将x赋值为x的倒数，但这样有个例外，当n是-2^31时，-n就超过了int范围，所以要让n转换成long
double myPow(double x, int n) {
    if (abs(x) < 1e-6) return x;  // x = 0
    if (abs(x) - 1 < 1e-6 && abs(x) - 1 > -1e-6) return x > 0 ? x : n & 1 ? x : -x;  // x = 1 or -1
    double res = 1.0;
    long m = static_cast<long>(n);
    if (m < 0) {
        x = 1.0 / x;
        m = -m;
    }
    while (m) {
        if (m & 1) res *= x;
        x *= x;
        m >>= 1;
    }
    return res;
}
