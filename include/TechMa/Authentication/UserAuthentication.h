/**
 * @file UserAuthentication.h
 * @brief Declaration of the User and AuthenticationService classes for managing authentication.
 */

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

/**
 * @enum UserRole
 * @brief Represents the possible roles a user can have.
 */
enum class UserRole
{
  GUEST,       ///< Guest user with limited access.
  TECHNICIAN,  ///< Technician user with extended privileges.
  ADMIN        ///< Administrator with full access.
};

/**
 * @class User
 * @brief Represents a user entity with credentials and a role.
 */
class User
{
public:
  User(int id, std::string username, std::string password_hash, UserRole role);

  int id() const;
  const std::string& username() const;
  const std::string& password_hash() const;
  UserRole role() const;

private:
  int m_id;
  std::string m_username;
  std::string m_password_hash;
  UserRole m_role;
};

/**
 * @class AuthenticationService
 * @brief Manages user authentication and session state.
 */
class AuthenticationService
{
public:
  static AuthenticationService& instance();

  void register_user(std::shared_ptr<User> user);
  bool login(const std::string& username, const std::string& password);
  void logout();
  std::shared_ptr<User> current_user() const;
  bool has_role(UserRole minimum_role) const;

private:
  AuthenticationService();
  std::unordered_map<std::string, std::shared_ptr<User>> m_users;
  std::shared_ptr<User> m_current_user = nullptr;
};

/**
 * @brief Hashes a plain-text password (stub implementation).
 * @param password The plain-text password.
 * @return A hashed string representation of the password.
 */
std::string hash_password(const std::string& password);