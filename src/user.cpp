#include"../inc/user.hpp"


// --- constructors ---
_LS::User::User() {};
_LS::User::User(const string& u, const string& p, const bool& a) : username(u), password(p), isAdmin(a) {}


// --- getters/setters ---
const std::string _LS::User::GetUsername() { return username; }
void _LS::User::SetUsername(const string& input) { username = input; }
const std::string _LS::User::GetPassword() { return password; }
void _LS::User::SetPassword(const string& input) { password = input; }
const std::string _LS::User::GetMessage() { return message; }
void _LS::User::SetMessage(const string& input) { message = input; }
const bool _LS::User::GetIsAdmin() { return isAdmin; }
void _LS::User::SetIsAdmin(const bool& input) { isAdmin = input; }


