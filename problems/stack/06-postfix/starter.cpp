// Lecture 5 — Postfix ifade hesaplama
// Girdi : expr — tek boşlukla ayrılmış postfix ifade, ör. "2 3 4 + *"
//         operandlar negatif olmayan tamsayılar, operatörler + - * /
// Çıktı : ifadenin değeri (int, tamsayı bölmesi)
//
// İpucu: istringstream in(expr); string tok; while (in >> tok) { ... }   stoi(tok) -> int
// std::stack YASAK, ele411.h'deki Stack'i kullanın.

int evaluatePostfix(string expr) {
    // Kodunuzu buraya yazın

    return 0;
}

int main() {
    cout << evaluatePostfix("2 3 4 + *") << endl;    // 14
    cout << evaluatePostfix("10 2 - 3 -") << endl;   // 5
    return 0;
}
