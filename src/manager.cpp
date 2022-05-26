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
    std::cout << '\n';
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
        case 0:
        {
            break;
        }
        default:
        {
            std::cout << "Invalid input, review the options and try again.\n";
        }
    }
}


// --- create account ---
const std::string _LS::AccountManager::CreateUsername()
{
    std::cout << "Create a username:\n> ";
    string username{};
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, username);
    std::replace(username.begin(), username.end(), ' ', '_');
    // verify if already exists
    // verify is suitable (e.g. contains a number)
    std::cout << '\n';
    return username;
}

const std::string _LS::AccountManager::CreatePassword()
{
    std::cout << "Create a password:\n> ";
    string password{};
    std::getline(std::cin, password);
    std::replace(password.begin(), password.end(), ' ', '_');
    // verify is suitable (e.g. contains a number)
    std::cout << '\n';
    return password;
}

void _LS::AccountManager::CreateAccount()
{
    string newUsername = CreateUsername();
    string newPassword = CreatePassword();
    //name_password_map[newUsername] = newPassword;
    userVec.push_back( std::make_unique<User>(newUsername, newPassword) );
    std::cout << "Your account has been created successfully.\n";
    std::cout << "Log in to your account to create a message.\n";
}


// --- existing account ---
void LogIn()
{
    
}

void _LS::AccountManager::CreateMessage(const string& username)
{
    std::cout << "Create a secret message:\n> ";
    string message{};
    std::getline(std::cin, message);

    auto it = userVec.begin();
    while(it!=userVec.end())
    {
        const unique_ptr<User>& u_ptr = *it;
        if(u_ptr->GetUsername() == username) { u_ptr->SetMessage(message); }
        ++it;
    }
}


// --- utility ---
void _LS::AccountManager::PrintNamesPasswords()
{
    for(auto& user : userVec)
    {
        std::cout << "Name: " << user->GetUsername() << " Password: " << user->GetPassword() << "\n";
    }
}

void _LS::AccountManager::PrintNamesMessages()
{
    for(auto& user : userVec)
    {
        std::cout << "Name: " << user->GetUsername() << "\n";
        std::cout << "Message: " << user->GetMessage() << "\n";
    }
}


// --- run ---
void _LS::AccountManager::Run()
{
    int request = -1;
    while(request != 0)
    {
        request = GetUserRequest();
        ProcessUserRequest(request);
    }

    //int request = GetUserRequest();
    //ProcessUserRequest(request);
/*     CreateMessage("jim"); // TEST
    PrintNamesPasswords();
    PrintNamesMessages(); */
}