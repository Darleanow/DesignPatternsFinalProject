#include "TechMa/Repository/InterventionRepository.h"

InterventionRepository &InterventionRepository::instance()
{
  static InterventionRepository repository;
  return repository;
}

int InterventionRepository::next_id()
{
  return m_current_id++;
}

void InterventionRepository::save(
    const std::shared_ptr<AIntervention> &intervention
)
{
  m_interventions[intervention->id()] = intervention;
  notify_all();
}

std::optional<std::shared_ptr<AIntervention>>
    InterventionRepository::find_by_id(int id) const
{
  auto it = m_interventions.find(id);
  if(it != m_interventions.end())
    return it->second;
  return std::nullopt;
}

std::vector<std::shared_ptr<AIntervention>>
    InterventionRepository::get_all() const
{
  std::vector<std::shared_ptr<AIntervention>> result;
  for(const auto &[_, intervention] : m_interventions)
    result.push_back(intervention);
  return result;
}

void InterventionRepository::clear()
{
  m_interventions.clear();
  notify_all();
}

void InterventionRepository::subscribe(QObject *subscriber)
{
  if(!subscriber)
    return;
  m_subscribers.push_back(subscriber);
}

void InterventionRepository::unsubscribe(QObject *subscriber)
{
  m_subscribers.erase(
      std::remove(m_subscribers.begin(), m_subscribers.end(), subscriber),
      m_subscribers.end()
  );
}

void InterventionRepository::notify_all() const
{
  for(auto *sub : m_subscribers) {
    QMetaObject::invokeMethod(
        sub, "on_repository_updated", Qt::QueuedConnection
    );
  }
}
