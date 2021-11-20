//===============================================
#ifndef _GQt_
#define _GQt_
//===============================================
#include "GInclude.h"
//===============================================
class GQt : public QObject {
    Q_OBJECT

public:
    enum eGType {
        eUnknown,
        eQWidget,
        eQPushButton,
        eQCheckBox,
        eQLabel,
        eQLineEdit,
        eQTextEdit,
        eQSpinBox,
        eQSlider,
        eQVBoxLayout,
        eQHBoxLayout,
        eLast
    };

public:
    GQt(QObject* _parent = 0);
    ~GQt();
    GQt& createQWidget();
    GQt& createQPushButton(const QString& _name);
    GQt& createQPushButton(const QString& _name, const QString& _key, QMap<QWidget*, QString>& _QWidgetMap);
    GQt& createQCheckBox(const QString& _name);
    GQt& createQCheckBox(const QString& _name, const QString& _key, QMap<QWidget*, QString>& _QWidgetMap);
    GQt& createQLabel(const QString& _text);
    GQt& createQLineEdit();
    GQt& createQLineEdit(const QString& _key, QMap<QWidget*, QString>& _QWidgetMap);
    GQt& createQTextEdit();
    GQt& createQSpinBox();
    GQt& createQSlider();
    GQt& createQVBoxLayout();
    GQt& createQHBoxLayout();
    GQt& addWidget(GQt& _widget);
    GQt& addLayout(GQt& _layout);
    GQt& addStretch(int _stretch = 0);
    GQt& setBuddy(GQt& _widget);
    GQt& setQWidget(QWidget* _widget);
    GQt& setWindowTitle(const QString& _title);
    GQt& setLayout(QWidget* _widget);
    GQt& setAlignment(Qt::Alignment _alignment);
    GQt& setRange(int _min, int _max);
    GQt& setText(const QString& _text);
    GQt& setDefault(bool _ok);
    GQt& setEnabled(bool _ok);
    GQt& connectObject(const char* _signal, const QObject* _member, const char* _slot);
    GQt& connectObject(const char* _signal, GQt& _member, const char* _slot);
    QWidget* getQWidget();
    QBoxLayout* getQBoxLayout();
    QString getText();
    QString getKey(int _argc, char** _argv, int _index);
    GQt& getKey(int _argc, char** _argv, int _index, QString& _key);
    bool isEmpty();
    bool isChecked();

private:
    eGType m_eGType;
    QWidget* m_QWidget;
    QPushButton* m_QPushButton;
    QCheckBox* m_QCheckBox;
    QLabel* m_QLabel;
    QLineEdit* m_QLineEdit;
    QTextEdit* m_QTextEdit;
    QSpinBox* m_QSpinBox;
    QSlider* m_QSlider;
    QVBoxLayout* m_QVBoxLayout;
    QHBoxLayout* m_QHBoxLayout;
};
//==============================================
#endif
//==============================================
