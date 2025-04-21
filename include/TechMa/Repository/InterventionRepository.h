#pragma once

#include "TechMa/Entities/AIntervention.h"

#include <QObject>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

class InterventionRepository
{
public:
  static InterventionRepository &instance();

  int                            next_id();

  void save(const std::shared_ptr<AIntervention> &intervention);
  std::optional<std::shared_ptr<AIntervention>> find_by_id(int id) const;
  std::vector<std::shared_ptr<AIntervention>>   get_all() const;
  void                                          clear();

  void                                          subscribe(QObject *subscriber);
  void unsubscribe(QObject *subscriber);

private:
  InterventionRepository() = default;
  void                                                    notify_all() const;

  int                                                     m_current_id = 1;
  std::unordered_map<int, std::shared_ptr<AIntervention>> m_interventions;
  std::vector<QObject *>                                  m_subscribers;
};
