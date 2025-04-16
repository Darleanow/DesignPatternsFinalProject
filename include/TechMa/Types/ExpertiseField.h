#pragma once

enum class ExpertiseField
{
  ELECTRICAL,  // Circuits, panels, power systems
  NETWORKING,  // Router, switches, cabling
  HVAC,        // Heating, ventilation, air conditioning
  PLUMBING,    // Water systems, pipes, leakage
  SECURITY,    // Cameras, access control, alarms
  SOFTWARE,    // OS Maintenance, scripts, diagnosis
  HARDWARE,    // Physical server repairs, BIOS, components
  FIRE_SAFETY, // Detectors, sprinklers, inspections
  STRUCTURAL,  // Building-related (doors, windows, ceilings)
  GENERALIST,  // Can handle basic tasks in every domain (complexity < medium)
};
