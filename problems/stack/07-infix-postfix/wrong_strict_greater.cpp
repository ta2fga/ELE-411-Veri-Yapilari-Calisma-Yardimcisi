// YANLIŞ: >= yerine > kullanıyor -> eşit öncelikte soldan birleşme bozuluyor (a-b-c -> abc--)
int prec(char op) { return (op == '*' || op == '/') ? 2 : (op == '+' || op == '-') ? 1 : 0; }
string infixToPostfix(string infix) {
    Stack s;
    string out;
    for (char ch : infix) {
        if (ch == ' ') continue;
        if (ch == '(') s.push(ch);
        else if (ch == ')') {
            while ((char)s.peek() != '(') { out += (char)s.peek(); s.pop(); }
            s.pop();
        } else if (prec(ch) > 0) {
            while (!s.isEmpty() && (char)s.peek() != '(' && prec((char)s.peek()) > prec(ch)) {
                out += (char)s.peek(); s.pop();
            }
            s.push(ch);
        } else out += ch;
    }
    while (!s.isEmpty()) { out += (char)s.peek(); s.pop(); }
    return out;
}
