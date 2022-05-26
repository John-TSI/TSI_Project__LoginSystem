#ifndef MANAGER_HPP
#define MANAGER_HPP

#include<vector>
#include<unordered_map>
#include<string>
#include"user.hpp"


namespace _LS // LoginSystem
{
    using std::vector;
    using std::unordered_map;

    class AccountManager
    {
        //vector<User> userVec{};
        unordered_map<int, string> ID_name_map{};
        unordered_map<int, bool> ID_locked_map{};
        unordered_map<string, string> name_password_map{};
        unordered_map<string, string> name_message_map{};

        public:
            // --- user request ---
            const int GetUserRequest();
            void ProcessUserRequest(const int);

            // --- create account ---
            const string CreateUsername();
            const string CreatePassword();
            void CreateAccount();

            // --- login ---
            void LogIn();
            void CheckCredentials();
            void RetrieveMessage();

            // --- utility ---
            void PrintNamePasswordMap(); // TEST

            // --- run ---
            void Run();
    };
}

#endif // MANAGER_HPP