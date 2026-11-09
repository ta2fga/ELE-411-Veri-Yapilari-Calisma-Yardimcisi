// YANLIŞ: sonda stack'in boş olduğunu kontrol etmiyor
bool isBalanced(string expr) {
    Stack s;
    for (char ch : expr) {
        if (ch == '(' || ch == '[' || ch == '{') s.push(ch);
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.isEmpty()) return false;
            char open = (ch == ')') ? '(' : (ch == ']') ? '[' : '{';
            if (s.peek() != open) return false;
            s.pop();
        }
    }
    return true;
}
