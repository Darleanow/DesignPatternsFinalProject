#include "TechMa/Views/Controllers/TechListController.h"
#include "TechMa/Views/Widgets/InterventionEditPanel.h"
#include "TechMa/Types/ExpertiseField.h"
#include "TechMa/Types/InterventionComplexity.h"

#include <QComboBox>
#include <QDateEdit>
#include <QFormLayout>
#include <QLineEdit>
#include <QAbstractItemView>
#include <QPushButton>
#include <QSpinBox>

InterventionEditPanel::InterventionEditPanel(QWidget* parent)
    : QWidget(parent)
{
    setup_ui();
    setup_connects();
    m_tech_controller = new TechListController(
        m_expertise_input,
        m_complexity_input,
        m_technician_input,
        this
    );
    setVisible(false);
}

InterventionEditPanel::~InterventionEditPanel()
{
}

void InterventionEditPanel::setup_ui()
{
    auto* layout = new QFormLayout(this);

    m_date_input = new QDateEdit(QDate::currentDate(), this);
    m_date_input->setCalendarPopup(true);
    layout->addRow("Date", m_date_input);

    m_duration_input = new QSpinBox(this);
    m_duration_input->setRange(1, 24);
    m_duration_input->setSuffix(" h");
    layout->addRow("Duration", m_duration_input);

    m_expertise_input = new QComboBox(this);
    for (auto field : {
        ExpertiseField::ELECTRICAL, ExpertiseField::NETWORKING,
        ExpertiseField::HVAC, ExpertiseField::PLUMBING,
        ExpertiseField::SECURITY, ExpertiseField::SOFTWARE,
        ExpertiseField::HARDWARE, ExpertiseField::FIRE_SAFETY,
        ExpertiseField::STRUCTURAL, ExpertiseField::GENERALIST
    }) {
        m_expertise_input->addItem(
            QString::fromStdString(to_string(field)),
            static_cast<int>(field)
        );
    }
    layout->addRow("Expertise", m_expertise_input);

    m_complexity_input = new QComboBox(this);
    m_complexity_input->addItems({"Easy", "Medium", "Hard", "Expert"});
    layout->addRow("Complexity", m_complexity_input);

    m_location_input = new QLineEdit(this);
    layout->addRow("Location", m_location_input);

    m_notes_input = new QLineEdit(this);
    layout->addRow("Notes", m_notes_input);

    m_technician_input = new QComboBox(this);
    layout->addRow("Technician", m_technician_input);

    m_save_button = new QPushButton("Save Changes", this);
    layout->addRow("", m_save_button);

    layout->setVerticalSpacing(12);
    layout->setContentsMargins(8, 8, 8, 8);
}

void InterventionEditPanel::setup_connects()
{
    auto setup_combo = [this](QComboBox* combo) {
        combo->setEditable(false);
        connect(combo, QOverload<int>::of(&QComboBox::activated), combo,
                [combo](int) {
                    combo->hidePopup();
                    if (auto* view = combo->view())
                        view->window()->close();
                });
    };

    setup_combo(m_expertise_input);
    setup_combo(m_complexity_input);
    setup_combo(m_technician_input);
}

void InterventionEditPanel::load(const InterventionData& data)
{
    m_id = data.id;
    auto d = data.date;
    m_date_input->setDate(
        QDate(int(d.year()), unsigned(d.month()), unsigned(d.day()))
    );
    m_duration_input->setValue(int(data.anticipated_duration.count()));
    m_expertise_input->setCurrentIndex(static_cast<int>(data.expertise_required));
    m_complexity_input->setCurrentIndex(static_cast<int>(data.complexity));
    m_location_input->setText(QString::fromStdString(data.location.address));
    m_notes_input->setText(QString::fromStdString(data.notes));

    m_tech_controller->update_technicians();

    int idx = 0;
    if (data.technician_id) {
        for (int i = 1; i < m_technician_input->count(); ++i) {
            if (m_technician_input->itemData(i).toInt() == *data.technician_id) {
                idx = i;
                break;
            }
        }
    }
    m_technician_input->setCurrentIndex(idx);
    setVisible(true);
}

void InterventionEditPanel::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
}

InterventionData InterventionEditPanel::to_data() const
{
    InterventionData data;
    data.id = m_id;
    auto d = m_date_input->date();
    data.date = std::chrono::year{d.year()} /
                unsigned(d.month()) /
                unsigned(d.day());
    data.anticipated_duration = std::chrono::hours{m_duration_input->value()};
    data.expertise_required =
        static_cast<ExpertiseField>(m_expertise_input->currentIndex());
    data.complexity =
        static_cast<InterventionComplexity>(m_complexity_input->currentIndex());
    data.location = Location{m_location_input->text().toStdString(), {0, 0}};
    data.notes = m_notes_input->text().toStdString();
    QVariant v = m_technician_input->currentData();
    data.technician_id = v.isValid() ? std::optional{v.toInt()} : std::nullopt;
    data.completed = false;
    return data;
}

QPushButton* InterventionEditPanel::save_button() const
{
    return m_save_button;
}
