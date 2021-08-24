//===============================================
#ifndef _GCalendar_
#define _GCalendar_
//===============================================
#include "GQtUi.h"
//===============================================
class GCalendar : public GQtUi {
    Q_OBJECT
    
public:
    GCalendar(QWidget* parent = 0);
    virtual ~GCalendar();
    void createPreviewGroupBox();
    void createGeneralOptionsGroupBox();
    void createDatesGroupBox();
    void createTextFormatsGroupBox();
    QComboBox* createColorComboBox();
    void firstDayChanged(int index);
    void selectionModeChanged(int index);
    void horizontalHeaderChanged(int index);
    void verticalHeaderChanged(int index);
    void weekdayFormatChanged();
    void weekendFormatChanged();
    void reformatHeaders();
    void reformatCalendarPage();

public slots:
	void onEvent(int year, int month);
	void onEvent(const QString& text);

private:
    QGroupBox* previewGroupBox;
    QGroupBox* generalOptionsGroupBox;
    QGroupBox* datesGroupBox;
    QGroupBox* textFormatsGroupBox;
    QCalendarWidget* calendar;
    QGridLayout* previewLayout;
    QComboBox* localeCombo;
    QComboBox* firstDayCombo;
    QComboBox* selectionModeCombo;
    QComboBox* horizontalHeaderCombo;
    QComboBox* verticalHeaderCombo;
    QComboBox* weekdayColorCombo;
    QComboBox* weekendColorCombo;
    QComboBox* headerTextFormatCombo;
    QLabel* localeLabel;
    QLabel* firstDayLabel;
    QLabel* selectionModeLabel;
    QLabel* horizontalHeaderLabel;
    QLabel* verticalHeaderLabel;
    QLabel* minimumDateLabel;
    QLabel* currentDateLabel;
    QLabel* maximumDateLabel;
    QLabel* weekdayColorLabel;
    QLabel* weekendColorLabel;
    QLabel* headerTextFormatLabel;
    QCheckBox* gridCheckBox;
    QCheckBox* navigationCheckBox;
    QCheckBox* firstFridayCheckBox;
    QCheckBox* mayFirstCheckBox;
    QDateEdit* minimumDateEdit;
    QDateEdit* currentDateEdit;
    QDateEdit* maximumDateEdit;
};
//==============================================
#endif
//==============================================
