#pragma once

#include "TechMa/Authentication/UserAuthentication.h"
#include "TechMa/Entities/AIntervention.h"
#include "TechMa/Repository/InterventionRepository.h"

#include <QObject>
#include <memory>
#include <optional>
#include <vector>

class InterventionRepositoryProxy
{
public:
  static InterventionRepositoryProxy           &instance();

  std::optional<std::shared_ptr<AIntervention>> find_by_id(int id) const;
  std::vector<std::shared_ptr<AIntervention>>   get_all() const;
  int                                           next_id();

  void save(const std::shared_ptr<AIntervention> &intervention);
  void clear();

  void subscribe(QObject *subscriber);
  void unsubscribe(QObject *subscriber);

private:
  InterventionRepositoryProxy() = default;
};