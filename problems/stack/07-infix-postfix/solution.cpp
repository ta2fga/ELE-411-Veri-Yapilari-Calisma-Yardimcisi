// Lecture 5 — Infix -> postfix dönüşümü (referans çözüm, ders pseudocode'una göre)

// Operatör önceliği: * ve / -> 2, + ve - -> 1
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

string infixToPostfix(string infix) {
    Stack opStack;          // operatörler ve '(' (char olarak) burada bekler
    string postfix = "";

    for (int i = 0; i < (int)infix.length(); i++) {
        char ch = infix[i];
        if (ch == ' ') {
            continue;                                   // boşlukları atla
        } else if (ch == '(') {
            opStack.push(ch);                           // '(' her zaman push
        } else if (ch == ')') {
            // '(' görene kadar operatörleri çıktıya aktar
            while ((char)opStack.peek() != '(') {
                postfix += (char)opStack.peek();
                opStack.pop();
            }
            opStack.pop();                              // '(' yi at
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Üstteki operatörün önceliği >= ise önce o çıkar (soldan birleşme)
            while (!opStack.isEmpty() && (char)opStack.peek() != '(' &&
                   precedence((char)opStack.peek()) >= precedence(ch)) {
                postfix += (char)opStack.peek();
                opStack.pop();
            }
            opStack.push(ch);
        } else {
            postfix += ch;                              // operand: doğrudan çıktıya
        }
    }
    // Kalan operatörleri ekle
    while (!opStack.isEmpty()) {
        postfix += (char)opStack.peek();
        opStack.pop();
    }
    return postfix;
}

int main() {
    cout << infixToPostfix("a - (b + c * d) / e") << endl;
    cout << infixToPostfix("a-b-c") << endl;
    return 0;
}
