// Lecture 1 — myMult (referans çözüm, ders kodu)
int myMult(int a, int b) {
    if (a == 1)                      // base case: 1 * b = b
        return b;
    return b + myMult(a - 1, b);     // a * b = b + (a-1) * b
}

int main() {
    cout << myMult(21, 6) << endl;
    return 0;
}
