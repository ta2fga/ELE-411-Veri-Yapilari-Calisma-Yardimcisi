// Lecture 5 — Infix -> postfix dönüşümü
// Girdi : infix — ör. "a - (b + c * d) / e"  (operandlar tek harf/rakam, boşluklar önemsiz)
// Çıktı : postfix string, boşluksuz — ör. "abcd*+e/-"
//
// Operatörler: + - * /   (* ve / önce; hepsi soldan birleşimli), parantez: ( )
// Stack int tutar; char da tamsayıdır: s.push('('), (char)s.peek()
// std::stack YASAK, ele411.h'deki Stack'i kullanın.

string infixToPostfix(string infix) {
    // Kodunuzu buraya yazın

    return "";
}

int main() {
    cout << infixToPostfix("a - (b + c * d) / e") << endl;   // abcd*+e/-
    cout << infixToPostfix("a-b-c") << endl;                 // ab-c-
    return 0;
}
