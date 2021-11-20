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
		eQDialogButtonBox,
        eLast
    };

public:
    GQt(QObject* _parent = 0);
    ~GQt();
    GQt& createQWidget(QWidget* _parent = 0);
    GQt& createQPushButton(const QString& _name, QWidget* _parent = 0);
    GQt& createQPushButton(const QString& _name, const QString& _key, QMap<QWidget*, QString>& _QWidgetMap, QWidget* _parent = 0);
    GQt& createQCheckBox(const QString& _name, QWidget* _parent = 0);
    GQt& createQCheckBox(const QString& _name, const QString& _key, QMap<QWidget*, QString>& _QWidgetMap, QWidget* _parent = 0);
    GQt& createQLabel(const QString& _text, QWidget* _parent = 0);
    GQt& createQLineEdit(QWidget* _parent = 0);
    GQt& createQLineEdit(const QString& _key, QMap<QWidget*, QString>& _QWidgetMap, QWidget* _parent = 0);
    GQt& createQTextEdit(QWidget* _parent = 0);
    GQt& createQSpinBox(QWidget* _parent = 0);
    GQt& createQSlider(QWidget* _parent = 0);
    GQt& createQVBoxLayout(QWidget* _parent = 0);
    GQt& createQHBoxLayout(QWidget* _parent = 0);
    GQt& createQDialogButtonBox(QWidget* _parent = 0);
    GQt& addWidget(GQt& _widget);
    GQt& addLayout(GQt& _layout);
    GQt& addStretch(int _stretch = 0);
    GQt& addButton(QDialogButtonBox::StandardButton _button);
    GQt& setBuddy(GQt& _widget);
    GQt& setQWidget(QWidget* _widget);
    GQt& setWindowTitle(const QString& _title);
    GQt& setLayout(QWidget* _widget);
    GQt& setAlignment(Qt::Alignment _alignment);
    GQt& setRange(int _min, int _max);
    GQt& setText(const QString& _text);
    GQt& setDefault(bool _ok);
    GQt& setEnabled(bool _ok);
    GQt& setEnabled(QDialogButtonBox::StandardButton _button, GQt& _widget);
    GQt& setEnabled(QDialogButtonBox::StandardButton _button, bool _ok);
    GQt& setValidator(const QString& _pattern, QWidget* _widget);
    GQt& connectObject(const char* _signal, const QObject* _member, const char* _slot);
    GQt& connectObject(const char* _signal, GQt& _member, const char* _slot);
    QWidget* getQWidget();
    QBoxLayout* getQBoxLayout();
    QString getText();
    QString getKey(int _argc, char** _argv, int _index);
    GQt& getKey(int _argc, char** _argv, int _index, QString& _key);
    Qt::CaseSensitivity getCaseSensitivity();
    bool isEmpty();
    bool isChecked();
    bool hasAcceptableInput();

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
    QDialogButtonBox* m_QDialogButtonBox;
};
//==============================================
#endif
//==============================================
