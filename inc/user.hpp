#ifndef USER_HPP
#define USER_HPP

#include<string>


namespace _LS // LoginSystem
{
    using std::string;

    class User
    {
        string username{};
        string password{};
        string message{};
    };
}

#endif // USER_HPP