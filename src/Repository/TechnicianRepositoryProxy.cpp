#include "TechMa/Repository/TechnicianRepositoryProxy.h"

AccessDeniedException::AccessDeniedException(const std::string &message)
    : std::runtime_error(message)
{
}

TechnicianRepositoryProxy &TechnicianRepositoryProxy::instance()
{
  static TechnicianRepositoryProxy proxy;
  return proxy;
}

std::optional<std::shared_ptr<ATechnician>>
    TechnicianRepositoryProxy::find_by_id(int id) const
{
  return TechnicianRepository::instance().find_by_id(id);
}

std::vector<std::shared_ptr<ATechnician>>
    TechnicianRepositoryProxy::get_all() const
{
  return TechnicianRepository::instance().get_all();
}

int TechnicianRepositoryProxy::next_id()
{
  return TechnicianRepository::instance().next_id();
}

void TechnicianRepositoryProxy::save(std::shared_ptr<ATechnician> tech)
{
  if(!AuthenticationService::instance().has_role(UserRole::ADMIN)) {
    throw AccessDeniedException("Admin privileges required to save technicians"
    );
  }
  TechnicianRepository::instance().save(tech);
}

bool TechnicianRepositoryProxy::remove_by_id(int id)
{
  if(!AuthenticationService::instance().has_role(UserRole::ADMIN)) {
    throw AccessDeniedException(
        "Admin privileges required to remove technicians"
    );
  }
  return TechnicianRepository::instance().remove_by_id(id);
}

void TechnicianRepositoryProxy::subscribe(ATechnicianObserver *observer)
{
  TechnicianRepository::instance().subscribe(observer);
}

void TechnicianRepositoryProxy::unsubscribe(ATechnicianObserver *observer)
{
  TechnicianRepository::instance().unsubscribe(observer);
}