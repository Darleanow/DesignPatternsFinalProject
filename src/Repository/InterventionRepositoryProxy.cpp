#include "TechMa/Repository/InterventionRepositoryProxy.h"
#include "TechMa/Repository/TechnicianRepositoryProxy.h"

InterventionRepositoryProxy &InterventionRepositoryProxy::instance()
{
  static InterventionRepositoryProxy proxy;
  return proxy;
}

std::optional<std::shared_ptr<AIntervention>>
    InterventionRepositoryProxy::find_by_id(int id) const
{
  return InterventionRepository::instance().find_by_id(id);
}

std::vector<std::shared_ptr<AIntervention>>
    InterventionRepositoryProxy::get_all() const
{
  return InterventionRepository::instance().get_all();
}

int InterventionRepositoryProxy::next_id()
{
  return InterventionRepository::instance().next_id();
}

void InterventionRepositoryProxy::save(
    const std::shared_ptr<AIntervention> &intervention
)
{
  if(!AuthenticationService::instance().has_role(UserRole::TECHNICIAN)) {
    throw AccessDeniedException(
        "You must be at least a member to save interventions"
    );
  }
  InterventionRepository::instance().save(intervention);
}

void InterventionRepositoryProxy::clear()
{
  if(!AuthenticationService::instance().has_role(UserRole::ADMIN)) {
    throw AccessDeniedException(
        "Admin privileges required to clear interventions"
    );
  }
  InterventionRepository::instance().clear();
}

void InterventionRepositoryProxy::subscribe(QObject *subscriber)
{
  InterventionRepository::instance().subscribe(subscriber);
}

void InterventionRepositoryProxy::unsubscribe(QObject *subscriber)
{
  InterventionRepository::instance().unsubscribe(subscriber);
}
