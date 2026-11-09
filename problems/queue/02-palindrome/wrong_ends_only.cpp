// YANLIŞ: sadece ilk ve son karakteri karşılaştırıyor
bool isPalindrome(string str) {
    if (str.empty()) return true;
    return str[0] == str[str.length() - 1];
}
