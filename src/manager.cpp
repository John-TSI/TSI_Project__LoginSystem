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
            printf("\033c");
            std::cout << "Invalid input, review the options and try again.\n";
        }
    }
}


// --- create account ---
const std::string _LS::AccountManager::CreateUsername()
{
    string username{};

    bool isValidUsername{false};
    while(!isValidUsername)
    {
        std::cout << "Create a username:\n> ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear input buffer
        std::getline(std::cin, username);
        std::replace(username.begin(), username.end(), ' ', '_');

        isValidUsername = ValidateUsername(username);
        // std::getline takes inserted '\n' out of input buffer, causing cin.ignore to disregard user input on next pass
        // next line puts a '\n' back into buffer to trigger cin.ignore, skipping to std::getline
        if(!isValidUsername){ std::cin.putback('\n'); }
    }
    std::cout << '\n';
    return username;
}

const std::string _LS::AccountManager::CreatePassword()
{
    string password{};
    
    bool isValidPassword{false};
    while(!isValidPassword)
    {
        std::cout << "Create a password:\n> ";
        std::getline(std::cin, password);
        std::replace(password.begin(), password.end(), ' ', '_');

        isValidPassword = ValidatePassword(password);
    }
    std::cout << '\n';
    return password;
}

void _LS::AccountManager::CreateAccount()
{
    string newUsername = CreateUsername();
    string newPassword = CreatePassword();
    userVec.push_back( std::make_unique<User>(newUsername, newPassword, false) );

    // hash and store password, add to User's previous passwords
    AppendHashedPassword( newUsername, HashPassword(newPassword) );
    userVec.back()->GetPreviousPasswords().push_back(newPassword);

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

bool _LS::AccountManager::VerifiedUsername(const string& username)
{
    return ( FindUser(username) != userVec.end() ); 
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

bool _LS::AccountManager::VerifiedPassword(const string& username, const string& password)
{
    return ( (*FindUser(username))->GetPassword() == password ); 
}

void _LS::AccountManager::LogIn()
{
    string username = RequestUsername();
    if( !VerifiedUsername(username) )
    {
        printf("\033c");
        std::cout << "Username not recognised.\nCheck your input and try again, or create an account.\n";
        return;
    } 
    string password = RequestPassword();
    if( !VerifiedPassword(username, password) )
    {
        printf("\033c");
        std::cout << "Input does not match the stored password for this user.\nCheck your input and try again.\n";
        return;
    }
    printf("\033c");
    std::cout << "Credentials accepted.\n";
    loginSuccessful = true;
    currentUser = *(*FindUser(username));
}


// --- user request ---
const int _LS::AccountManager::GetUserRequest()
{
    std::cout << "\nPlease make a selection:\n";
    std::cout << "--------------------------------------\n";
    std::cout << "1 ...... Create a new message\n";
    std::cout << "2 ...... Retrieve your message\n";
    std::cout << "3 ...... Change your password\n";
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
        case 3:
        {
            ChangePassword();
            break;
        }
        case 0:
        {
            printf("\033c");
            loginSuccessful = false;
            currentUser = {};
            break;
        }
        default:
        {
            printf("\033c");
            std::cout << "Invalid input, review the options and try again.\n";
        }
    }
}

void _LS::AccountManager::CreateMessage()
{
    printf("\033c");
    std::cout << "Create a secret message:\n> ";
    string message{};
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, message);

    auto it = FindUser(currentUser.GetUsername());
    printf("\033c");
    std::cout << 
    (
        message.length() < 1
        ? ( (*it)->GetMessage().length() < 1 )
            ? "Empty message detected. No changes have been saved."
            : "Empty message detected. Your previous message has been deleted."
        : "Your secret message has been saved."
    )
    << '\n';

    (*it)->SetMessage(message);
}

void _LS::AccountManager::RetrieveMessage()
{
    printf("\033c");
    auto it = FindUser(currentUser.GetUsername());
    std::cout << 
    ( 
        (*it)->GetMessage().length() < 1
        ? "You have not yet stored a message."
        : "Your secret message:\n" + (*it)->GetMessage() 
    ) 
    << '\n';
}

void _LS::AccountManager::ChangePassword()
{
    printf("\033c");
    string newPassword{};
    auto it = FindUser(currentUser.GetUsername());

    bool isValidPassword{false};
    while(!isValidPassword)
    {
        std::cout << "Enter your new password:\n> ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, newPassword);

        isValidPassword = ValidatePassword(newPassword);
        for(auto& oldPassword : (*it)->GetPreviousPasswords())
        {
            if(newPassword == oldPassword)
            {
                printf("\033c");
                std::cout << "New password cannot be identical to a previously stored password.\n\n";
                isValidPassword = false;
            }
        }
        if(!isValidPassword){ std::cin.putback('\n'); }
    }

    (*it)->SetPassword(newPassword);
    AppendHashedPassword( currentUser.GetUsername(), HashPassword(newPassword) );
    userVec.back()->GetPreviousPasswords().push_back(newPassword);
    printf("\033c");
    std::cout << "Your password has been updated.\n";
}


// --- admin request ---
const int _LS::AccountManager::GetAdminRequest()
{
    std::cout << "\nPlease make a selection:\n";
    std::cout << "---------------------------------\n";
    std::cout << "1 ...... View all users\n";
    std::cout << "2 ...... Delete a user\n";
    std::cout << "3 ...... View hashed passwords\n";
    std::cout << "0 ...... Return to the login menu\n";
    std::cout << "---------------------------------\n> ";
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
        case 3:
        {
            ViewHashedPasswords();
            break;
        }
        case 0:
        {
            printf("\033c");
            loginSuccessful = false;
            currentUser = {};
            break;
        }
        default:
        {
            printf("\033c");
            std::cout << "Invalid input, review the options and try again.\n";
        }
    }
}


// --- admin tasks ---
void _LS::AccountManager::ViewUsers()
{
    printf("\033c");
    std::cout << "USERNAME : PASSWORD\n-------------------\n";
    for(auto& u_ptr : userVec)
    {
        std::cout << u_ptr->GetUsername() << " : " << u_ptr->GetPassword() << '\n';
    }
    std::cout << '\n';
}

void _LS::AccountManager::DeleteUser()
{
    if(userVec.size() < 2)  // only admin account exists, not deletable.
    {
        printf("\033c"); 
        std::cout << "No deletable user accounts exist on the system.\n"; 
        return; 
    }

    printf("\033c");
    std::cout << "Enter the username of the User to be deleted:\n> ";
    string username{};
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, username);
    std::replace(username.begin(), username.end(), ' ', '_');

    if(username == "admin")  // prevent deletion of admin account
    {
        printf("\033c");
        std::cout << "Cannot delete admin account.\n";
        return;
    }

    if( FindUser(username) == userVec.end() )
    {
        printf("\033c");
        std::cout << "Username not recognised.\nCheck your input and try again.\n";
        return;
    }
 
    userVec.erase( FindUser(username) );
    hashedPasswords.erase(username);
    printf("\033c");
    std::cout << "The specified User has been deleted from the system.\n";
}

void _LS::AccountManager::ViewHashedPasswords()
{
    printf("\033c");
    std::cout << "USERNAME : HASHED PASSWORD\n--------------------------\n";
    for(auto& [username, hashedPassword] : hashedPasswords)
    {
        std::cout << username << " : " << hashedPassword << '\n';
    }
    std::cout << '\n';
}


// --- utility ---
_LS::UVec::iterator _LS::AccountManager::FindUser(const string& username)
{
    auto is_user = [&](unique_ptr<User>& u_ptr){ return (u_ptr->GetUsername() == username); };
    return std::find_if( userVec.begin(), userVec.end(), is_user );
}

bool _LS::AccountManager::ValidateUsername(const string& username)
{
    if(username.length() < 4)  // check input length
    {
        printf("\033c");
        std::cout << "Usernames must be at least four characters long.\n\n";
        return false;
    }
    if( FindUser(username) != userVec.end() )  // check username does not already exist
    {
        printf("\033c");
        std::cout << "The username is not available, try another.\n\n";
        return false;
    }
    return true;
}

bool _LS::AccountManager::ValidatePassword(const string& password)
{
    if(password.length() < 4)  // check input length
    {
        printf("\033c");
        std::cout << "Passwords must be at least four characters long.\n\n";
        return false;
    }
    if( std::find_if(password.begin(), password.end(), isdigit) == password.end() )  // check password contains at least one number
    {
        printf("\033c");
        std::cout << "Passwords must contain at least one number.\n\n";
        return false;
    }
    return true;
}

size_t _LS::AccountManager::HashPassword(const string& password)
{
    return std::hash<string>{}(password);
}

void _LS::AccountManager::AppendHashedPassword(const string& username, const size_t& hashedPassword)
{
    hashedPasswords.insert( {username, hashedPassword} );
}


// --- run ---
void _LS::AccountManager::Run()
{
    int request1 = -1;
    while(request1 != 0)
    {
        // create account / log in
        request1 = GetUnknownUserRequest();
        ProcessUnknownUserRequest(request1);

        // non-admin user
        if(loginSuccessful && !currentUser.GetIsAdmin())
        {
            int request2 = -1;
            while(request2 != 0)
            {
                request2 = GetUserRequest();
                ProcessUserRequest(request2);
            }
        }

        // admin user
        if(loginSuccessful && currentUser.GetIsAdmin())
        {
            int request2 = -1;
            while(request2 != 0)
            {
                request2 = GetAdminRequest();
                ProcessAdminRequest(request2);
            }
        }
    }
}


// --- testing ---
const std::vector<std::unique_ptr<_LS::User>>& _LS::AccountManager::GetUsers()
{
    return userVec;
}