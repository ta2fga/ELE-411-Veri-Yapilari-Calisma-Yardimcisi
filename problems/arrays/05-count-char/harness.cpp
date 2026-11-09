static void h_case(const char* s, char c, int exp) {
    CHECK(std::string("countChar(\"") + s + "\", '" + c + "')", countChar(s, c), exp);
}
TEST("Boş string", "s = \"\", c = 'a'") { h_case("", 'a', 0); }
TEST("Yok", "s = \"hello\", c = 'z'") { h_case("hello", 'z', 0); }
TEST("Birkaç kez", "s = \"data structures\", c = 't'") { h_case("data structures", 't', 3); }
TEST("Büyük/küçük harf", "s = \"AaAa\", c = 'a'") { h_case("AaAa", 'a', 2); }
TEST("Boşluk", "s = \"a b c\", c = ' '") { h_case("a b c", ' ', 2); }
TEST("Hepsi", "s = \"zzzz\", c = 'z'") { h_case("zzzz", 'z', 4); }
