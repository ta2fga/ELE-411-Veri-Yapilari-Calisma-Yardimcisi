// YANLIŞ: ilk recursive çağrıda hedef ve yardımcı karıştırılmış
void hanoi(int n, char source, char destination, char auxiliary) {
    if (n == 1) { cout << "Move the top disk from " << source << " to " << destination << endl; return; }
    hanoi(n - 1, source, destination, auxiliary);
    cout << "Move the top disk from " << source << " to " << destination << endl;
    hanoi(n - 1, auxiliary, destination, source);
}
