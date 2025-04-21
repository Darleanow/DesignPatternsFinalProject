#include "TechMa/Views/Pages/InterventionPage.h"
#include "TechMa/Facade/InterventionCreatorFacade.h"
#include "TechMa/Repository/InterventionRepository.h"
#include "TechMa/Views/Widgets/CreateInterventionDialog.h"
#include "TechMa/Views/Widgets/EntityEditorLayout.h"
#include "TechMa/Views/Widgets/InterventionEditPanel.h"
#include "TechMa/Views/Widgets/InterventionsListView.h"

#include <QPushButton>
#include <QVBoxLayout>

InterventionPage::InterventionPage(QWidget *parent) : QWidget(parent)
{
  setup_ui();
  setup_connects();
}

void InterventionPage::setup_ui()
{
  m_layout =
      new EntityEditorLayout("Interventions", "Create Intervention", this);
  m_create_button = m_layout->action_button();

  m_list_view = new InterventionsListView(this);
  m_layout->set_left_widget(m_list_view);

  m_edit_panel = new InterventionEditPanel(this);
  m_layout->set_right_widget(m_edit_panel);
  m_edit_panel->setVisible(false);

  auto *wrapper_layout = new QVBoxLayout(this);
  wrapper_layout->addWidget(m_layout);
  setLayout(wrapper_layout);

  m_create_dialog = new CreateInterventionDialog(this);
}

void InterventionPage::setup_connects()
{
  connect(m_create_button, &QPushButton::clicked, this, [this]() {
    if(m_create_dialog->exec() == QDialog::Accepted) {
      auto data = m_create_dialog->intervention_data();
      if(data.has_value()) {
        data->id = InterventionRepository::instance().next_id();
        auto intervention =
            InterventionCreatorFacade::create_intervention(data.value());
        InterventionRepository::instance().save(intervention);
      }
    }
  });

  connect(
      m_list_view, &InterventionsListView::intervention_selected, this,
      [this](int id) {
        m_selected_intervention_id = id;
        auto opt = InterventionRepository::instance().find_by_id(id);
        if(opt.has_value()) {
          const auto &intervention = opt.value();
          m_edit_panel->load(intervention->data());
        }
      }
  );

  connect(m_edit_panel->save_button(), &QPushButton::clicked, this, [this]() {
    if(!m_selected_intervention_id.has_value())
      return;

    auto data    = m_edit_panel->to_data();
    data.id      = *m_selected_intervention_id;
    auto updated = InterventionCreatorFacade::create_intervention(data);
    InterventionRepository::instance().save(updated);
  });
}
