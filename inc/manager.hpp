#ifndef MANAGER_HPP
#define MANAGER_HPP

#include<vector>
#include<memory>
#include<string>
#include"user.hpp"


namespace _LS // LoginSystem
{
    using std::vector;
    using std::unique_ptr;

    class AccountManager
    {
        vector<unique_ptr<User>> userVec{};
        bool loginSuccessful{false};
        string currentUser_username{};
        bool currentUser_isAdmin{false};
        User currentUser{};

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

            // --- admin request ---
            const int GetAdminRequest();
            void ProcessAdminRequest(const int);

            // --- admin tasks ---
            void ViewUsers();
            void DeleteUser();

            // --- utility ---
            int FindUserIndex(const string&);

            // --- run ---
            void Run();
    };
}

#endif // MANAGER_HPP