/**
 * @file InterventionsListView.h
 * @brief Declares the InterventionsListView class, a QListView for displaying and selecting interventions.
 */

#pragma once

#include <QListView>

class QStringListModel;

/**
 * @class InterventionsListView
 * @brief A custom QListView that displays a list of interventions and emits selection signals.
 * 
 * This widget is used in the UI to allow users to browse and select interventions from a list.
 */
class InterventionsListView : public QListView
{
  Q_OBJECT;

public:
  /**
   * @brief Constructs the list view and initializes its UI.
   * 
   * @param parent Optional parent QWidget.
   */
  explicit InterventionsListView(QWidget *parent = nullptr);

  /**
   * @brief Destructor.
   */
  ~InterventionsListView() override;

signals:
  /**
   * @brief Emitted when a user selects an intervention from the list.
   * 
   * @param id The ID of the selected intervention.
   */
  void intervention_selected(int id);

public slots:
  /**
   * @brief Slot called when the intervention repository is updated.
   * 
   * Updates the list to reflect the current interventions.
   */
  void on_repository_updated();

private:
  /**
   * @brief Initializes the list view UI components.
   */
  void setup_ui();

  /**
   * @brief Connects internal signals and slots for user interaction.
   */
  void setup_connects();

  QStringListModel *m_model = nullptr; ///< Model used to store and display the list of interventions.
};