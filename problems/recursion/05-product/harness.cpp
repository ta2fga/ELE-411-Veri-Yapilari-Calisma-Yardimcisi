static void h_case(int x, int y) {
    CHECK("product(" + std::to_string(x) + ", " + std::to_string(y) + ")", product(x, y), x * y);
}
TEST("sd.pdf örneği", "product(5, 2)") { h_case(5, 2); }
TEST("Sıra farkı", "product(2, 5)") { h_case(2, 5); }
TEST("Sıfır", "product(0, 7), product(7, 0)") { h_case(0, 7); h_case(7, 0); }
TEST("Negatif x", "product(-3, 4)") { h_case(-3, 4); }
TEST("Negatif y", "product(3, -4)") { h_case(3, -4); }
TEST("İkisi negatif", "product(-3, -4)") { h_case(-3, -4); }
TEST("Bir", "product(1, 99), product(99, 1)") { h_case(1, 99); h_case(99, 1); }
