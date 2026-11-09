// Test kodu: countItem
static void h_case(std::initializer_list<int> items, int target, int expected) {
    Stack s = makeStack(items);
    std::string before = stackToString(s);
    int r = countItem(s, target);
    CHECK("dönüş değeri", r, expected);
    CHECK_TEXT("çağrıdan sonra stack (alt→üst)", stackToString(s), before);
}
TEST("Boş stack", "myStack = [], targetItem = 4") { h_case({}, 4, 0); }
TEST("Tek eleman, eşleşiyor", "myStack = [4], targetItem = 4") { h_case({4}, 4, 1); }
TEST("Hedef hiç yok", "myStack = [1, 2, 3], targetItem = 9") { h_case({1, 2, 3}, 9, 0); }
TEST("Hepsi hedef", "myStack = [7, 7, 7, 7], targetItem = 7") { h_case({7, 7, 7, 7}, 7, 4); }
TEST("Karışık: üstte, altta, ortada", "myStack = [2, 5, 2, 7, 2], targetItem = 2") { h_case({2, 5, 2, 7, 2}, 2, 3); }
TEST("Bir kez, en altta", "myStack = [8, 1, 1, 3], targetItem = 8") { h_case({8, 1, 1, 3}, 8, 1); }
TEST("Negatif hedef", "myStack = [-3, 4, -3, 0], targetItem = -3") { h_case({-3, 4, -3, 0}, -3, 2); }
