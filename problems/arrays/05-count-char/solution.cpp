// Study 10 — Karakter sayma (referans çözüm)
int countChar(string s, char c) {
    int count = 0;
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] == c)
            count++;
    return count;
}

int main() {
    cout << countChar("data structures", 't') << endl;
    return 0;
}
