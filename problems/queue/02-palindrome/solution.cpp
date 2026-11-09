// Study 12 — Stack + Queue ile palindrom (referans çözüm, Lecture 5 Figure 13-3)
bool isPalindrome(string str) {
    Stack s;                          // tersini verir (LIFO)
    Queue q;                          // düzünü verir (FIFO)
    for (int i = 0; i < (int)str.length(); i++) {
        s.push(str[i]);
        q.enqueue(str[i]);
    }
    while (!s.isEmpty()) {            // ikisinde de aynı sayıda eleman var
        if (s.peek() != q.peekFront())
            return false;             // ilk uyuşmazlık: palindrom değil
        s.pop();
        q.dequeue();
    }
    return true;
}

int main() {
    cout << boolalpha << isPalindrome("abcba") << " " << isPalindrome("geek") << endl;
    return 0;
}
