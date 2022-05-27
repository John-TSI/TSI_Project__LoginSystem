#ifndef USER_HPP
#define USER_HPP

#include<string>


namespace _LS // LoginSystem
{
    using std::string;

    class User
    {
        string username{}, password{}, message{};
        bool isAdmin{false}, isLocked{false};

        public:
            // --- constructor ---
            User(const string&, const string&, const bool&);

            // --- getters/setters ---
            const string GetUsername();
            void SetUsername(const string&);
            const string GetPassword();
            void SetPassword(const string&);
            const string GetMessage();
            void SetMessage(const string&);
            const bool GetIsAdmin();
            void SetIsAdmin(const bool&);
    };
}

#endif // USER_HPP