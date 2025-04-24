/**
 * @file TechniciansListView.h
 * @brief Declares the TechniciansListView class, a QListView for displaying and selecting technicians.
 */

#pragma once

#include "TechMa/Observer/ATechnicianObserver.h"

#include <QListView>

class QWidget;
class QStringListModel;

/**
 * @class TechniciansListView
 * @brief Custom list view displaying available technicians and observing changes in the technician repository.
 *
 * This view updates automatically when the technician repository changes
 * and emits signals when a technician is selected.
 */
class TechniciansListView : public QListView, public ATechnicianObserver
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the list view and initializes its UI and behavior.
   * 
   * @param parent Optional parent widget.
   */
  explicit TechniciansListView(QWidget *parent = nullptr);

  /**
   * @brief Destructor.
   */
  ~TechniciansListView();

  /**
   * @brief Called when the technician repository is updated.
   * 
   * This method refreshes the displayed technician list.
   */
  void on_repository_updated() override;

signals:
  /**
   * @brief Emitted when a technician is selected from the list.
   * 
   * @param id The ID of the selected technician.
   */
  void technician_selected(int id);

private:
  /**
   * @brief Initializes UI properties and internal models.
   */
  void setup_ui();

  /**
   * @brief Connects interaction events to internal logic.
   */
  void setup_connects();

  QStringListModel *m_model; ///< Model storing technician names for display.
};