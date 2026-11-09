// Lecture 5 — Dengeli parantez kontrolü (referans çözüm)

// Kapanış karakterine karşılık gelen açılışı döndürür.
char matchingOpen(char close) {
    if (close == ')') return '(';
    if (close == ']') return '[';
    return '{';
}

bool isBalanced(string expr) {
    Stack s;                                   // açılış parantezlerini tutar
    for (int i = 0; i < (int)expr.length(); i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);                        // açılış: push
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.isEmpty())                   // eşleşecek açılış yok
                return false;
            if (s.peek() != matchingOpen(ch))  // tür uyuşmuyor: "{(})" gibi
                return false;
            s.pop();                           // eşleşti
        }
        // diğer karakterler yok sayılır
    }
    return s.isEmpty();                        // kapanmamış açılış kalmamalı
}

int main() {
    cout << boolalpha;
    cout << isBalanced("a{b(c[d]e)f}g") << endl;
    cout << isBalanced("{(})") << endl;
    cout << isBalanced("((") << endl;
    return 0;
}
