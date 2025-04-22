#pragma once

#include "TechMa/Authentication/UserAuthentication.h"
#include "TechMa/Entities/ATechnician.h"
#include "TechMa/Observer/ATechnicianObserver.h"
#include "TechMa/Repository/TechnicianRepository.h"

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

class AccessDeniedException : public std::runtime_error
{
public:
  AccessDeniedException(const std::string &message);
};

class TechnicianRepositoryProxy
{
public:
  static TechnicianRepositoryProxy           &instance();

  std::optional<std::shared_ptr<ATechnician>> find_by_id(int id) const;
  std::vector<std::shared_ptr<ATechnician>>   get_all() const;
  int                                         next_id();

  void save(std::shared_ptr<ATechnician> tech);
  bool remove_by_id(int id);

  void subscribe(ATechnicianObserver *observer);
  void unsubscribe(ATechnicianObserver *observer);

private:
  TechnicianRepositoryProxy() = default;
};