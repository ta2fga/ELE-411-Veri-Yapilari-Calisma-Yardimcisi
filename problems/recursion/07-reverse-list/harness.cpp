static void h_case(std::initializer_list<std::string> items, const char* exp) {
    StringNode* head = makeStringList(items);
    std::string before = listToString(head);
    std::string got = ele411::capture([&] { printReverse(head); });
    CHECK_TEXT("ekran çıktısı", ele411::trimOutput(got), exp);
    CHECK_TEXT("liste değişmemeli", listToString(head), before);
    deleteList(head);
}
TEST("Boş liste", "headPtr = nullptr") { h_case({}, ""); }
TEST("Tek düğüm", "\"ali\"") { h_case({"ali"}, "ali"); }
TEST("Üç düğüm", "\"ali\" -> \"veli\" -> \"deli\"") { h_case({"ali", "veli", "deli"}, "deli\nveli\nali"); }
TEST("Tekrarlı", "\"a\" -> \"b\" -> \"a\" -> \"c\"") { h_case({"a", "b", "a", "c"}, "c\na\nb\na"); }
TEST("Beş düğüm", "\"1\" -> ... -> \"5\"") { h_case({"1", "2", "3", "4", "5"}, "5\n4\n3\n2\n1"); }
