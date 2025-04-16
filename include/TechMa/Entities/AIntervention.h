#pragma once
#include <chrono>

class AIntervention
{
public:
  ~AIntervention() = delete;

private:
  std::chrono::year_month_day m_date;
  // Technician
  std::chrono::minutes m_anticipated_duration;
  std::chrono::minutes m_actual_duration;
};
