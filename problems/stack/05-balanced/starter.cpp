// Lecture 5 — Dengeli parantez kontrolü: ( ) [ ] { }
// Girdi : expr — string
// Çıktı : parantezler dengeliyse true, değilse false
//
// İpucu: Stack int tutar; char da tamsayıdır -> s.push('{'), s.peek() == '{'
// std::stack YASAK, ele411.h'deki Stack'i kullanın.

bool isBalanced(string expr) {
    // Kodunuzu buraya yazın

    return false;
}

int main() {
    cout << boolalpha;
    cout << isBalanced("a{b(c[d]e)f}g") << endl;   // true
    cout << isBalanced("{(})") << endl;            // false
    cout << isBalanced("((") << endl;              // false
    return 0;
}
