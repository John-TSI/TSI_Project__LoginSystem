#include<gtest/gtest.h>
#include<string>
#include"../inc/manager.hpp"


// --- SUITE: construction/initialisation ---
TEST(ManagerConstruction, AdminAccountCreated)
{
    _LS::AccountManager AM;
    EXPECT_EQ(AM.GetUsers().size(), 1);
}


// --- SUITE: input validation ---
TEST(InputValidation, UsernameTooShort)
{
    _LS::AccountManager AM;
    const std::string username{"bad"};
    EXPECT_FALSE(AM.ValidateUsername(username)); 
}

TEST(InputValidation, UsernameUnavailable)
{
    _LS::AccountManager AM;
    _LS::User user1{"username1", "password1", false};
    AM.AddUser(user1);
    EXPECT_FALSE(AM.ValidateUsername("username1")); 
}

TEST(InputValidation, PasswordTooShort)
{
    _LS::AccountManager AM;
    const std::string password{"bad"};
    EXPECT_FALSE(AM.ValidatePassword(password));
}

TEST(InputValidation, PasswordDoesNotContainDigit)
{
    _LS::AccountManager AM;
    const std::string password{"SufficientlyLongPassword"};
    EXPECT_FALSE(AM.ValidatePassword(password));
}


// --- SUITE: login verification ---
TEST(LoginVerification, UsernameFound)
{
    _LS::AccountManager AM;
    _LS::User user1{"username1", "password1", false};
    AM.AddUser(user1);
    EXPECT_TRUE(AM.VerifiedUsername("username1"));
}

TEST(LoginVerification, UsernameNotFound)
{
    _LS::AccountManager AM;
    _LS::User user1{"username1", "password1", false};
    AM.AddUser(user1);
    EXPECT_FALSE(AM.VerifiedUsername("notA_User"));
}

TEST(LoginVerification, PasswordAccepted)
{
    _LS::AccountManager AM;
    _LS::User user1{"username1", "password1", false};
    AM.AddUser(user1);
    EXPECT_TRUE(AM.VerifiedPassword("username1", "password1"));
}

TEST(LoginVerification, PasswordRejected)
{
    _LS::AccountManager AM;
    _LS::User user1{"username1", "password1", false};
    AM.AddUser(user1);
    EXPECT_FALSE(AM.VerifiedPassword("username1", "forgotMyPassword1"));
}


// ---- gtest driver code ----
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}