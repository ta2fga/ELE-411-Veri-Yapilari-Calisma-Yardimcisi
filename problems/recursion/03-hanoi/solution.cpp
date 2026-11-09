// Lecture 1 — Hanoi Kuleleri (referans çözüm, ders kodu)
void hanoi(int n, char source, char destination, char auxiliary) {
    if (n == 1) {                                   // base case: tek disk
        cout << "Move the top disk from " << source << " to " << destination << endl;
        return;
    }
    hanoi(n - 1, source, auxiliary, destination);   // n-1 diski yardımcıya
    cout << "Move the top disk from " << source << " to " << destination << endl;  // en büyüğü hedefe
    hanoi(n - 1, auxiliary, destination, source);   // n-1 diski hedefe
}

int main() {
    hanoi(3, 'A', 'C', 'B');
    return 0;
}
