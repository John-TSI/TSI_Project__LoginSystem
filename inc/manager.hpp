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

        public:
            // --- user request ---
            const int GetUserRequest();
            void ProcessUserRequest(const int);

            // --- create account ---
            const string CreateUsername();
            const string CreatePassword();
            void CreateAccount();

            // --- log in ---
            const string RequestUsername();
            const string RequestPassword();
            bool VerifyUsername(const string&);
            bool VerifyPassword(const string&, const string&);
            void LogIn();

            // --- message ---
            void CreateMessage(const string&);
            void RetrieveMessage();

            // --- admin ---

            // --- utility ---
            int FindUserIndex(const string&);
            void PrintNamesPasswords(); // TEST
            void PrintNamesMessages(); // TEST

            // --- run ---
            void Run();
    };
}

#endif // MANAGER_HPP