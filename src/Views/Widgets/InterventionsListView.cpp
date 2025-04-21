#include "TechMa/Views/Widgets/InterventionsListView.h"
#include "TechMa/Repository/InterventionRepository.h"
#include "TechMa/Repository/TechnicianRepository.h"
#include "TechMa/Types/ExpertiseField.h"

#include <QDate>
#include <QStringListModel>

namespace {
const QStringList complexity_names {"Easy", "Medium", "Hard", "Expert"};
}

InterventionsListView::InterventionsListView(QWidget *parent)
    : QListView(parent)
{
  setup_ui();
  setup_connects();
}

InterventionsListView::~InterventionsListView() = default;

void InterventionsListView::setup_ui()
{
  m_model = new QStringListModel(this);
  setModel(m_model);
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  InterventionRepository::instance().subscribe(this);
  on_repository_updated();
}

void InterventionsListView::setup_connects()
{
  connect(this, &QListView::clicked, this, [this](const QModelIndex &index) {
    int        row = index.row();
    const auto all = InterventionRepository::instance().get_all();
    if(row >= 0 && row < all.size())
      emit intervention_selected(all[row]->id());
  });
}

void InterventionsListView::on_repository_updated()
{
  QStringList list;
  const auto  all   = InterventionRepository::instance().get_all();
  const auto &techs = TechnicianRepository::instance().get_all();

  for(auto &iv : all) {
    const auto &d = iv->data();

    int         year  = static_cast<int>(d.date.year());
    int         month = static_cast<int>(static_cast<unsigned>(d.date.month()));
    int         day   = static_cast<int>(static_cast<unsigned>(d.date.day()));
    QDate       qdate(year, month, day);

    QString expertise = QString::fromStdString(to_string(d.expertise_required));
    QString complexity = complexity_names.value(int(d.complexity));
    QString duration =
        QStringLiteral("%1h").arg(d.anticipated_duration.count());
    QString location = QString::fromStdString(d.location.address);

    QString tech_name = "Unassigned";
    if(d.technician_id) {
      for(auto &t : techs) {
        if(t->get_id() == *d.technician_id) {
          tech_name = QString::fromStdString(t->get_name());
          break;
        }
      }
    }

    QString s = QStringLiteral("[%1] %2 — %3 — %4 — %5 — %6")
                    .arg(qdate.toString("yyyy‑MM‑dd"))
                    .arg(expertise)
                    .arg(complexity)
                    .arg(duration)
                    .arg(location)
                    .arg(tech_name);

    list << s;
  }

  m_model->setStringList(list);
}
