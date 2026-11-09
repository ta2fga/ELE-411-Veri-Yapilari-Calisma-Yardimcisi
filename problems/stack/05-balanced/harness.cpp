// Test kodu: isBalanced
static void h_case(const char* expr, bool expected) {
    CHECK(std::string("isBalanced(\"") + expr + "\")", isBalanced(expr), expected);
}
TEST("Boş string", "expr = \"\"") { h_case("", true); }
TEST("Parantez yok", "expr = \"abc\"") { h_case("abc", true); }
TEST("Basit dengeli", "expr = \"{}\", \"()\", \"[]\"") { h_case("{}", true); h_case("()", true); h_case("[]", true); }
TEST("İç içe ve karışık", "expr = \"a{b(c[d]e)f}g\", \"{{}}[]()\"") { h_case("a{b(c[d]e)f}g", true); h_case("{{}}[]()", true); }
TEST("Tür uyuşmazlığı", "expr = \"{(})\", \"(]\"") { h_case("{(})", false); h_case("(]", false); }
TEST("Kapanmamış açılış", "expr = \"((\", \"{[()]\"") { h_case("((", false); h_case("{[()]", false); }
TEST("Fazla kapanış", "expr = \"())\", \"}\"") { h_case("())", false); h_case("}", false); }
TEST("Ters sıra", "expr = \"}{\", \")(\"") { h_case("}{", false); h_case(")(", false); }
