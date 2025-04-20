#include "TechMa/Views/Controllers/TechListController.h"

#include <QVariant>

TechListController::TechListController(QComboBox* expertise_input,
                                       QComboBox* complexity_input,
                                       QComboBox* technician_input,
                                       QObject* parent)
    : QObject(parent),
      m_expertise_input(expertise_input),
      m_complexity_input(complexity_input),
      m_technician_input(technician_input)
{
    setup_connections();
    TechnicianRepository::instance().subscribe(this);
    update_technicians();
}

TechListController::~TechListController() {
    TechnicianRepository::instance().unsubscribe(this);
}

void TechListController::setup_connections() {
    connect(m_expertise_input,
            QOverload<int>::of(&QComboBox::activated),
            this,
            [this](int){ update_technicians(); });
    connect(m_complexity_input,
            QOverload<int>::of(&QComboBox::activated),
            this,
            [this](int){ update_technicians(); });
}

void TechListController::update_technicians() {
    rebuild_list();
}

void TechListController::on_repository_updated() {
    update_technicians();
}

void TechListController::rebuild_list() {
    QVariant prev = m_technician_input->currentData();
    int prev_id  = prev.isValid() ? prev.toInt() : -1;

    m_technician_input->clear();
    m_technician_input->addItem("— Aucun —", QVariant());

    bool has_expertise = m_expertise_input->currentData().isValid();
    QString first_txt  = m_complexity_input->itemText(0);
    bool placeholder   = first_txt.contains("Select", Qt::CaseInsensitive);
    bool has_complexity= placeholder
                         ? m_complexity_input->currentIndex()>0
                         : true;
    if (!has_expertise || !has_complexity) {
        m_technician_input->setEnabled(false);
        return;
    }

    auto required = static_cast<ExpertiseField>(
        m_expertise_input->currentData().toInt());
    int  cidx     = placeholder
                    ? m_complexity_input->currentIndex()-1
                    : m_complexity_input->currentIndex();
    auto comp     = static_cast<InterventionComplexity>(cidx);
    bool allow_gen= comp<=InterventionComplexity::MEDIUM;

    for (auto tech : TechnicianRepository::instance().get_all()) {
        if (tech->has_expertise(required) ||
           (allow_gen && tech->has_expertise(ExpertiseField::GENERALIST)))
        {
            m_technician_input->addItem(
              QString::fromStdString(tech->get_name()),
              tech->get_id()
            );
        }
    }

    int to_select = 0;
    if (prev_id>=0) {
      for (int i=1;i<m_technician_input->count();++i) {
        if (m_technician_input->itemData(i).toInt()==prev_id) {
          to_select = i;
          break;
        }
      }
    }
    m_technician_input->setCurrentIndex(to_select);
    m_technician_input->setEnabled(true);
}
