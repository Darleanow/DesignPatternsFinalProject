#pragma once

class ATechnicianObserver
{
public:
  virtual ~ATechnicianObserver()       = default;
  virtual void on_repository_updated() = 0;
};
