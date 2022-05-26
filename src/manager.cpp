#include<iostream>
#include<algorithm>
#include<limits>
#include"../inc/manager.hpp"


// --- user request ---
const int _LS::AccountManager::GetUserRequest()
{
    std::cout << "\nPlease make a selection:\n";
    std::cout << "--------------------------------------\n";
    std::cout << "1 ...... Create a new account\n";
    std::cout << "2 ...... Log in to an existing account\n";
    std::cout << "0 ...... Exit the program\n";
    std::cout << "--------------------------------------\n> ";
    int request{0};
    std::cin >> request;
    return request;
}

void _LS::AccountManager::ProcessUserRequest(const int req)
{
    switch(req)
    {
        case 1:
        {
            CreateAccount();
            break;
        }
        case 2:
        {
            //LogIn();
            break;
        }
        // case 0 (quit program) handled externally to this method
        default:
        {
            std::cout << "Invalid input, review the options and try again.\n";
        }
    }
}


// --- create account ---
const _LS::string _LS::AccountManager::CreateUsername()
{
    std::cout << "Create a username:\n> ";
    string username{};
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, username);
    std::replace(username.begin(), username.end(), ' ', '_');
    // verify if already exists
    // verify is suitable (e.g. contains a number)
    return username;
}

const _LS::string _LS::AccountManager::CreatePassword()
{
    std::cout << "Create a password:\n> ";
    string password{};
    std::getline(std::cin, password);
    std::replace(password.begin(), password.end(), ' ', '_');
    // verify is suitable (e.g. contains a number)
    return password;
}

void _LS::AccountManager::CreateAccount()
{
    string newUsername = CreateUsername();
    string newPassword = CreatePassword();
    name_password_map[newUsername] = newPassword;
}

// --- login ---


// --- utility ---
void _LS::AccountManager::PrintNamePasswordMap()
{
    for(auto& [name, pwd] : name_password_map)
    {
        std::cout << "Name: " << name << " Password: " << pwd << "\n";
    }
}


// --- run ---
void _LS::AccountManager::Run()
{
    int request = GetUserRequest();
    ProcessUserRequest(request);
    PrintNamePasswordMap();
}