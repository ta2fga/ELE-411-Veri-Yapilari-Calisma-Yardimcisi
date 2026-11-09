static void h_case(const char* s, const char* exp) {
    std::string got = ele411::capture([&] { writeBackward(s); });
    CHECK_TEXT(std::string("ekran çıktısı"), ele411::trimOutput(got), exp);
}
TEST("Ders örneği", "s = \"cat\"") { h_case("cat", "tac"); }
TEST("Boş string", "s = \"\"") { h_case("", ""); }
TEST("Tek karakter", "s = \"a\"") { h_case("a", "a"); }
TEST("Palindrom", "s = \"abba\"") { h_case("abba", "abba"); }
TEST("Boşluklu", "s = \"hello world\"") { h_case("hello world", "dlrow olleh"); }
