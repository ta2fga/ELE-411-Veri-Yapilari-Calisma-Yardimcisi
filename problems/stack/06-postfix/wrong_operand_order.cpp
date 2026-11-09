// YANLIŞ: operand sırası ters (ilk alınanı sol operand sanıyor)
int evaluatePostfix(string expr) {
    Stack s;
    istringstream in(expr);
    string tok;
    while (in >> tok) {
        if (tok == "+" || tok == "-" || tok == "*" || tok == "/") {
            int a = s.peek(); s.pop();
            int b = s.peek(); s.pop();
            if (tok == "+") s.push(a + b);
            else if (tok == "-") s.push(a - b);
            else if (tok == "*") s.push(a * b);
            else s.push(b == 0 ? 0 : a / b);
        } else s.push(stoi(tok));
    }
    return s.peek();
}
