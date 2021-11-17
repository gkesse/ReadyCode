//===============================================
#ifndef _GQt_
#define _GQt_
//===============================================
#include "GInclude.h"
//===============================================
class GQt : public QObject {
	Q_OBJECT

public:
    GQt(QObject* _parent = 0);
    ~GQt();
    GQt& createButton(const QString& _name, const QString& _key);
    GQt& createTextEdit();
    GQt& createVBoxLayout();
    GQt& createHBoxLayout();
    GQt& addWidget(const GQt& _widget);
    GQt& addLayout(const GQt& _layout);
    GQt& setLayout(QWidget* _widget);
    GQt& setAlignment(Qt::Alignment _alignment);
    GQt& connectObject(const char* _signal, const QObject* _member, const char* _slot);

private:
    QMap<QWidget*, QString> m_QWidgetMap;
    QWidget* m_QWidget;
    QBoxLayout* m_QBoxLayout;
    QPushButton* m_QPushButton;
    QTextEdit* m_QTextEdit;
    QVBoxLayout* m_QVBoxLayout;
    QHBoxLayout* m_QHBoxLayout;

};
//==============================================
#endif
//==============================================
