// Lecture 5 — Postfix ifade hesaplama (referans çözüm)

int evaluatePostfix(string expr) {
    Stack s;
    istringstream in(expr);
    string tok;
    while (in >> tok) {                      // boşluklara göre parça parça oku
        bool isOperator = (tok.length() == 1 &&
                           (tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/'));
        if (!isOperator) {
            s.push(stoi(tok));               // operand: push
        } else {
            int op2 = s.peek(); s.pop();     // ÜSTTEKİ = sağ operand
            int op1 = s.peek(); s.pop();     // altındaki = sol operand
            int result;
            switch (tok[0]) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                default:  result = op1 / op2; break;
            }
            s.push(result);                  // sonucu geri koy
        }
    }
    return s.peek();                         // geçerli ifadede tek eleman kalır
}

int main() {
    cout << evaluatePostfix("2 3 4 + *") << endl;
    cout << evaluatePostfix("10 2 - 3 -") << endl;
    return 0;
}
