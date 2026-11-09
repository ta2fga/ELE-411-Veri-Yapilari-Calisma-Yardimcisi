// Study 6 — recursive çarpma (referans çözüm, sd.pdf'in negatif sayıları da çalıştıran hali)
int product(int x, int y) {
    if (y == 0)                       // base case: x * 0 = 0
        return 0;
    if (y < 0)                        // negatif y: işareti dışarı al
        return -product(x, -y);       // x * y = -(x * (-y))
    return x + product(x, y - 1);     // x * y = x + x * (y - 1)
}

int main() {
    cout << product(5, 2) << endl;
    cout << product(3, -4) << endl;
    return 0;
}
