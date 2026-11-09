static void h_case(const char* s, bool exp) { CHECK(std::string("isPalindrome(\"") + s + "\")", isPalindrome(s), exp); }
TEST("Boş string", "\"\"") { h_case("", true); }
TEST("Tek karakter", "\"a\"") { h_case("a", true); }
TEST("Çift uzunluk", "\"abba\", \"geeg\"") { h_case("abba", true); h_case("geeg", true); }
TEST("Tek uzunluk", "\"abcba\"") { h_case("abcba", true); }
TEST("Palindrom değil", "\"geek\", \"ab\"") { h_case("geek", false); h_case("ab", false); }
TEST("Sadece uçlar eşit", "\"abca\"") { h_case("abca", false); }
TEST("Büyük/küçük harf", "\"Aa\"") { h_case("Aa", false); }
