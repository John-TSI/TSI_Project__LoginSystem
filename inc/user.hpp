#ifndef USER_HPP
#define USER_HPP

#include<string>
#include<vector>


namespace _LS // LoginSystem
{
    using std::string;
    using std::vector;

    class User
    {
        string username{}, password{}, message{};
        vector<string> previousPasswords{};
        bool isAdmin{false};

        public:
            // --- constructors ---
            User();
            User(const string&, const string&, const bool&);

            // --- getters/setters ---
            const string GetUsername();
            void SetUsername(const string&);
            const string GetPassword();
            void SetPassword(const string&);
            vector<string>& GetPreviousPasswords();
            const string GetMessage();
            void SetMessage(const string&);
            const bool GetIsAdmin();
            void SetIsAdmin(const bool&);
    };
}

#endif // USER_HPP