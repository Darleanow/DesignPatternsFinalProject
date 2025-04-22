#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

enum class UserRole
{
  GUEST,
  TECHNICIAN,
  ADMIN
};

class User
{
public:
  User(int id, std::string username, std::string password_hash, UserRole role);

  int                id() const;
  const std::string &username() const;
  const std::string &password_hash() const;
  UserRole           role() const;

private:
  int         m_id;
  std::string m_username;
  std::string m_password_hash;
  UserRole    m_role;
};

class AuthenticationService
{
public:
  static AuthenticationService &instance();

  void                          register_user(std::shared_ptr<User> user);
  bool login(const std::string &username, const std::string &password);
  void logout();
  std::shared_ptr<User> current_user() const;
  bool                  has_role(UserRole minimum_role) const;

private:
  AuthenticationService();

  std::unordered_map<std::string, std::shared_ptr<User>> m_users;
  std::shared_ptr<User> m_current_user = nullptr;
};

std::string hash_password(const std::string &password);