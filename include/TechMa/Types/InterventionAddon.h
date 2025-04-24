/**
 * @file InterventionAddon.h
 * @brief Declares the InterventionAddon enum class representing optional features for interventions.
 */

#pragma once

/**
 * @enum InterventionAddon
 * @brief Represents optional features or enhancements that can be added to an intervention.
 */
enum class InterventionAddon
{
  GPS_TRACKING,    ///< Enables GPS-based tracking for the intervention.
  ATTACHMENTS,     ///< Allows attaching files or documents to the intervention.
  LIVE_FEEDBACK,   ///< Enables real-time feedback during the intervention process.
  CHECKLIST,       ///< Provides a checklist for tasks or verification steps.
  EXTRA_SECURITY,  ///< Adds additional security measures to the process.
  PRIORITY_TAG,    ///< Marks the intervention as high priority.
  AUDIT_TRAIL,     ///< Logs all actions and changes for audit purposes.
  BACKUP_CREATION  ///< Automatically creates a backup before the intervention.
};