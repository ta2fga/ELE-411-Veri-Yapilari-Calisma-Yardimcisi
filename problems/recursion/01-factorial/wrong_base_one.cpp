// YANLIŞ: base case n == 1 -> factorial(0) hiç bitmez (stack overflow)
int factorial(int n) {
    if (n == 1) return 1;
    return n * factorial(n - 1);
}
