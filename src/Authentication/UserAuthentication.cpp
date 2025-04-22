#include "TechMa/Authentication/UserAuthentication.h"

User::User(
    int id, std::string username, std::string password_hash, UserRole role
)
    : m_id(id),
      m_username(std::move(username)),
      m_password_hash(std::move(password_hash)),
      m_role(role)
{
}

int User::id() const
{
  return m_id;
}

const std::string &User::username() const
{
  return m_username;
}

const std::string &User::password_hash() const
{
  return m_password_hash;
}

UserRole User::role() const
{
  return m_role;
}

AuthenticationService &AuthenticationService::instance()
{
  static AuthenticationService service;
  return service;
}

AuthenticationService::AuthenticationService()
{
  register_user(std::make_shared<User>(
      1, "admin", hash_password("admin123"), UserRole::ADMIN
  ));
  register_user(std::make_shared<User>(
      2, "tech", hash_password("tech123"), UserRole::TECHNICIAN
  ));
  register_user(std::make_shared<User>(
      3, "guest", hash_password("guest123"), UserRole::GUEST
  ));
}

void AuthenticationService::register_user(std::shared_ptr<User> user)
{
  m_users[user->username()] = user;
}

bool AuthenticationService::login(
    const std::string &username, const std::string &password
)
{
  auto it = m_users.find(username);
  if(it == m_users.end() || it->second->password_hash() != password) {
    return false;
  }

  m_current_user = it->second;
  return true;
}

void AuthenticationService::logout()
{
  m_current_user = nullptr;
}

std::shared_ptr<User> AuthenticationService::current_user() const
{
  return m_current_user;
}

bool AuthenticationService::has_role(UserRole minimum_role) const
{
  if(!m_current_user)
    return false;

  int user_role_value     = static_cast<int>(m_current_user->role());
  int required_role_value = static_cast<int>(minimum_role);

  return user_role_value >= required_role_value;
}

std::string hash_password(const std::string &password)
{
  return password;
}