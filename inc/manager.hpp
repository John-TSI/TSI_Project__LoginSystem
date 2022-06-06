#ifndef MANAGER_HPP
#define MANAGER_HPP

#include<vector>
#include<unordered_map>
#include<memory>
#include<string>
#include"user.hpp"


namespace _LS // LoginSystem
{
    using std::vector;
    using std::unordered_map;
    using std::unique_ptr;

    class AccountManager
    {
        vector<unique_ptr<User>> userVec{};
        bool loginSuccessful{false};
        User currentUser{};

        unordered_map<string, size_t> passwordHashmap{};

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

            // --- message ---
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
            int FindUserIndex(const string&);
            size_t HashPassword(const string&);
            void AppendHashedPassword(const size_t&);

            // --- run ---
            void Run();
    };
}

#endif // MANAGER_HPP