// YANLIŞ: sd.pdf'teki çözüm — y negatifse y hiç 0 olmaz (stack overflow)
int product(int x, int y) {
    if (x < y) return product(y, x);
    else if (y != 0) return (x + product(x, y - 1));
    else return 0;
}
