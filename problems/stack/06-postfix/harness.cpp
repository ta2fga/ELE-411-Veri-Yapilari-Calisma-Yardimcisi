// Test kodu: evaluatePostfix
static void h_case(const char* expr, int expected) {
    CHECK(std::string("evaluatePostfix(\"") + expr + "\")", evaluatePostfix(expr), expected);
}
TEST("Ders örneği", "expr = \"2 3 4 + *\"  (= 2 * (3 + 4))") { h_case("2 3 4 + *", 14); }
TEST("Tek operand", "expr = \"5\"") { h_case("5", 5); }
TEST("Çıkarma sırası", "expr = \"10 2 - 3 -\"  (= (10 - 2) - 3)") { h_case("10 2 - 3 -", 5); }
TEST("Bölme sırası", "expr = \"12 4 /\", \"7 2 /\"") { h_case("12 4 /", 3); h_case("7 2 /", 3); }
TEST("Öncelik karışık", "expr = \"2 3 4 * + 5 -\"  (= 2 + 3*4 - 5)") { h_case("2 3 4 * + 5 -", 9); }
TEST("Çok basamaklı", "expr = \"100 20 30 + -\"  (= 100 - (20 + 30))") { h_case("100 20 30 + -", 50); }
TEST("Negatif ara sonuç", "expr = \"3 8 - 2 *\"  (= (3 - 8) * 2)") { h_case("3 8 - 2 *", -10); }
