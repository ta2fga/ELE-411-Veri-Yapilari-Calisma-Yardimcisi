// Test kodu: removeAll
static void h_case(std::initializer_list<int> items, int target, const char* expected) {
    Stack s = makeStack(items);
    removeAll(s, target);
    CHECK_TEXT("sonuç stack (alt→üst)", stackToString(s), expected);
}
TEST("Boş stack", "myStack = [], targetItem = 3") { h_case({}, 3, "[]"); }
TEST("Tek eleman = hedef", "myStack = [3], targetItem = 3") { h_case({3}, 3, "[]"); }
TEST("Hedef yok", "myStack = [1, 2, 3], targetItem = 9") { h_case({1, 2, 3}, 9, "[1, 2, 3]"); }
TEST("Hepsi hedef", "myStack = [4, 4, 4], targetItem = 4") { h_case({4, 4, 4}, 4, "[]"); }
TEST("Üstte, altta ve ortada", "myStack = [7, 1, 7, 2, 7], targetItem = 7") { h_case({7, 1, 7, 2, 7}, 7, "[1, 2]"); }
TEST("Yan yana tekrarlar", "myStack = [1, 5, 5, 2, 5, 3], targetItem = 5") { h_case({1, 5, 5, 2, 5, 3}, 5, "[1, 2, 3]"); }
TEST("Diğer tekrarlar korunmalı", "myStack = [2, 9, 2, 9, 3], targetItem = 9") { h_case({2, 9, 2, 9, 3}, 9, "[2, 2, 3]"); }
