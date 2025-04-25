/**
 * @file TechListController.h
 * @brief Declares the TechListController class, a Qt-based controller for managing technician selection UI.
 */

#pragma once

#include "TechMa/Observer/ATechnicianObserver.h"

#include <QObject>

class QComboBox;

/**
 * @class TechListController
 * @brief Controls UI elements related to technician selection and observes technician repository updates.
 * 
 * This class connects expertise and complexity combo boxes to a dynamically updated list of technicians,
 * following the observer pattern to stay in sync with the technician repository.
 */
class TechListController : public QObject, public ATechnicianObserver
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs a TechListController.
   * 
   * @param expertise_input Pointer to the QComboBox for selecting expertise.
   * @param complexity_input Pointer to the QComboBox for selecting complexity.
   * @param technician_input Pointer to the QComboBox for displaying technicians.
   * @param parent Optional parent QObject for memory management.
   */
  TechListController(
      QComboBox *expertise_input, QComboBox *complexity_input,
      QComboBox *technician_input, QObject *parent = nullptr
  );

  /**
   * @brief Destructor (override).
   */
  ~TechListController() override;

  /**
   * @brief Updates the technician list based on current combo box selections.
   */
  void update_technicians();

protected:
  /**
   * @brief Reacts to updates in the technician repository.
   * 
   * Called automatically when the repository notifies its observers.
   */
  void on_repository_updated() override;

private:
  QComboBox *m_expertise_input;   ///< Combo box for selecting expertise.
  QComboBox *m_complexity_input;  ///< Combo box for selecting complexity.
  QComboBox *m_technician_input;  ///< Combo box to display technician options.

  /**
   * @brief Sets up Qt signal/slot connections.
   */
  void setup_connections();

  /**
   * @brief Rebuilds the technician list in the UI.
   */
  void rebuild_list();
};