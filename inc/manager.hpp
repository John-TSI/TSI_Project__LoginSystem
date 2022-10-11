#ifndef MANAGER_HPP
#define MANAGER_HPP

#include<unordered_map>
#include<memory>
#include"user.hpp"


namespace _LS // LoginSystem
{
    using std::unordered_map;
    using std::unique_ptr;
    using UVec = vector<unique_ptr<User>>;

    class AccountManager
    {
        vector<unique_ptr<User>> userVec{};
        bool loginSuccessful{false};
        User currentUser{};

        unordered_map<string, size_t> hashedPasswords{};

        public:
            // --- constructor ---
            AccountManager();

            // --- unknown user request ---
            const int GetUnknownUserRequest();
            void ProcessUnknownUserRequest(const int);

            // --- create account ---
            const string CreateUsername();
            const string CreatePassword();
            void CreateAccount();

            // --- log in ---
            const string RequestUsername();
            bool VerifyUsername(const string&);
            const string RequestPassword();
            bool VerifyPassword(const string&, const string&);
            void LogIn();

            // --- user request ---
            const int GetUserRequest();
            void ProcessUserRequest(const int);

            // --- user tasks ---
            void CreateMessage();
            void RetrieveMessage();
            void ChangePassword();

            // --- admin request ---
            const int GetAdminRequest();
            void ProcessAdminRequest(const int);

            // --- admin tasks ---
            void ViewUsers();
            void DeleteUser();
            void ViewHashedPasswords();

            // --- utility ---
            UVec::iterator FindUser(const string&);
            size_t HashPassword(const string&);
            void AppendHashedPassword(const string&, const size_t&);

            // --- run ---
            void Run();
    };
}

#endif // MANAGER_HPP