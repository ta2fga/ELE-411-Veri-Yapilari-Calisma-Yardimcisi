// Lecture 1 — Factorial (referans çözüm)
int factorial(int n) {
    if (n == 0)                      // base case: 0! = 1
        return 1;
    return n * factorial(n - 1);     // n! = n * (n-1)!
}

int main() {
    cout << factorial(5) << endl;
    return 0;
}
