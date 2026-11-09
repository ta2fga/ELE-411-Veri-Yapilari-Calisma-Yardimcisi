// Study 5 — String'i tersten yazdır (referans çözüm, Lecture 1 writeBackward)
void writeBackward(string s) {
    int length = s.length();
    if (length > 0) {                              // base case: boş string -> bir şey yapma
        cout << s[length - 1];                     // son karakteri yaz
        writeBackward(s.substr(0, length - 1));    // kalan kısmı tersten yaz
    }
}

int main() {
    writeBackward("cat");
    cout << endl;
    return 0;
}
