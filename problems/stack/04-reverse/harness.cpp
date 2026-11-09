// Test kodu: reverseStack
static void h_case(std::initializer_list<int> items, const char* expected) {
    Stack s = makeStack(items);
    reverseStack(s);
    CHECK_TEXT("sonuç stack (alt→üst)", stackToString(s), expected);
}
TEST("Boş stack", "st = []") { h_case({}, "[]"); }
TEST("Tek eleman", "st = [7]") { h_case({7}, "[7]"); }
TEST("İki eleman", "st = [1, 2]") { h_case({1, 2}, "[2, 1]"); }
TEST("Dört eleman", "st = [1, 2, 3, 4]") { h_case({1, 2, 3, 4}, "[4, 3, 2, 1]"); }
TEST("Tekrarlı elemanlar", "st = [5, 5, 1, 2, 2]") { h_case({5, 5, 1, 2, 2}, "[2, 2, 1, 5, 5]"); }
TEST("Negatif ve sıfır", "st = [-1, 0, 3, -8, 6, 9]") { h_case({-1, 0, 3, -8, 6, 9}, "[9, 6, -8, 3, 0, -1]"); }
TEST("İki kez ters = orijinal", "st = [1, 2, 3]; reverseStack iki kez") {
    Stack s = makeStack({1, 2, 3});
    reverseStack(s);
    reverseStack(s);
    CHECK_TEXT("sonuç stack (alt→üst)", stackToString(s), "[1, 2, 3]");
}
