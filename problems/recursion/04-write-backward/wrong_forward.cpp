// YANLIŞ: önce recursive çağrı sonra ilk karakter değil, ilk karakter önce yazılıyor -> düz yazar
void writeBackward(string s) {
    if (s.length() > 0) { cout << s[0]; writeBackward(s.substr(1)); }
}
