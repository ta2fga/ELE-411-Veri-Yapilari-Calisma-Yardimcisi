// YANLIŞ: b yerine a ekliyor
int myMult(int a, int b) {
    if (a == 1) return b;
    return a + myMult(a - 1, b);
}
