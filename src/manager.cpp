#include<iostream>
#include<algorithm>
#include<limits>
#include"../inc/manager.hpp"


// --- constructor ---
_LS::AccountManager::AccountManager() // creates an admin account on construction
{
    userVec.push_back( std::make_unique<User>("admin", "passw0rd", true) );
}


// --- unknown user request ---
const int _LS::AccountManager::GetUnknownUserRequest()
{
    //printf("\033c"); // clears console
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

void _LS::AccountManager::ProcessUnknownUserRequest(const int req)
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
            LogIn();
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
    // verify does not already exist
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
    userVec.push_back( std::make_unique<User>(newUsername, newPassword, false) );
    printf("\033c");
    std::cout << "Your account has been created successfully.\n";
    std::cout << "Log in to your account to create a message.\n";
}


// --- log in ---
const std::string _LS::AccountManager::RequestUsername()
{
    std::cout << "Enter your username:\n> ";
    string username{};
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, username);
    std::replace(username.begin(), username.end(), ' ', '_');
    std::cout << '\n';
    return username;
}

bool _LS::AccountManager::VerifyUsername(const string& username)
{
    auto it = userVec.begin() + FindUserIndex(username);
    return ( it != userVec.end() ); 
}

const std::string _LS::AccountManager::RequestPassword()
{
    std::cout << "Enter your password:\n> ";
    string password{};
    std::getline(std::cin, password);
    std::replace(password.begin(), password.end(), ' ', '_');
    std::cout << '\n';
    return password;
}

bool _LS::AccountManager::VerifyPassword(const string& username, const string& password)
{
    auto it = userVec.begin() + FindUserIndex(username);
    return ((*it)->GetPassword() == password); 
}

void _LS::AccountManager::LogIn()
{
    string username = RequestUsername();
    if(!VerifyUsername(username))
    {
        printf("\033c");
        std::cout << "Username not recognised.\nCheck your input and try again, or create an account.\n";
        return;
    } 
    string password = RequestPassword();
    if(!VerifyPassword(username, password))
    {
        printf("\033c");
        std::cout << "Input does not match the stored password for this user.\nCheck your input and try again.\n";
        return;
    }
    printf("\033c");
    std::cout << "Login successful.\n";
    loginSuccessful = true;
    currentUser_username = username;
    // TEST
    auto it = userVec.begin() + FindUserIndex(username);
    currentUser = *(*it);
}


// --- user request ---
const int _LS::AccountManager::GetUserRequest()
{
    //printf("\033c");
    std::cout << "\nPlease make a selection:\n";
    std::cout << "--------------------------------------\n";
    std::cout << "1 ...... Create a new message\n";
    std::cout << "2 ...... Retrieve your message\n";
    std::cout << "0 ...... Return to the login menu\n";
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
            CreateMessage();
            break;
        }
        case 2:
        {
            RetrieveMessage();
            break;
        }
        case 0:
        {
            printf("\033c");
            loginSuccessful = false;
            currentUser_username = "";
            break;
        }
        default:
        {
            std::cout << "Invalid input, review the options and try again.\n";
        }
    }
}


// --- message ---
void _LS::AccountManager::CreateMessage()
{
    printf("\033c");
    std::cout << "Create a secret message:\n> ";
    string message{};
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, message);

    auto it = userVec.begin() + FindUserIndex(currentUser_username);
    (*it)->SetMessage(message);
    printf("\033c");
    std::cout << "Your secret message has been saved.\n";
}

void _LS::AccountManager::RetrieveMessage()
{
    printf("\033c");
    std::cout << "Your secret message:\n";
    auto it = userVec.begin() + FindUserIndex(currentUser_username);
    std::cout << (*it)->GetMessage() << '\n';
}


// --- admin request ---
const int _LS::AccountManager::GetAdminRequest()
{
    //printf("\033c");
    std::cout << "\nPlease make a selection:\n";
    std::cout << "--------------------------------------\n";
    std::cout << "1 ...... View all users\n";
    std::cout << "2 ...... Delete a user\n";
    std::cout << "0 ...... Return to the login menu\n";
    std::cout << "--------------------------------------\n> ";
    int request{0};
    std::cin >> request;
    std::cout << '\n';
    return request;
}

void _LS::AccountManager::ProcessAdminRequest(const int req)
{
    switch(req)
    {
        case 1:
        {
            ViewUsers();
            break;
        }
        case 2:
        {
            DeleteUser();
            break;
        }
        case 0:
        {
            printf("\033c");
            loginSuccessful = false;
            currentUser_username = "";
            break;
        }
        default:
        {
            std::cout << "Invalid input, review the options and try again.\n";
        }
    }
}


// --- admin tasks ---
void _LS::AccountManager::ViewUsers()
{

}

void _LS::AccountManager::DeleteUser()
{

}


// --- utility ---
int _LS::AccountManager::FindUserIndex(const string& username)
{
    auto is_user = [&](unique_ptr<User>& u_ptr){ return (u_ptr->GetUsername() == username); };
    return std::find_if( userVec.begin(), userVec.end(), is_user ) - userVec.begin();
}


// --- run ---
void _LS::AccountManager::Run()
{
    int request1 = -1;
    while(request1 != 0)
    {
        request1 = GetUnknownUserRequest();
        ProcessUnknownUserRequest(request1);

        if(loginSuccessful)
        {
            int request2 = -1;
            while(request2 != 0)
            {
                request2 = GetUserRequest();
                ProcessUserRequest(request2);
            }
        }
    }
}