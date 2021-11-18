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
    GQt& createQTextEdit();
    GQt& createQSpinBox();
    GQt& createQSlider();
    GQt& createQVBoxLayout();
    GQt& createQHBoxLayout();
    GQt& addWidget(GQt& _widget);
    GQt& addLayout(GQt& _layout);
    GQt& setQWidget(QWidget* _widget);
    GQt& setWindowTitle(const QString& _title);
    GQt& setLayout(QWidget* _widget);
    GQt& setAlignment(Qt::Alignment _alignment);
    GQt& setRangeQSlider(int _min, int _max);
    GQt& setRangeQSpinBox(int _min, int _max);
    GQt& connectObject(const char* _signal, const QObject* _member, const char* _slot);
    QWidget* getQWidget();
    QBoxLayout* getQBoxLayout();
    GQt& getDataQTextEdit(std::string& _data);
    GQt& getKey(int _argc, char** _argv, int _index, QString& _key);
    bool isEmptyQTextEdit();

private:
    eGType m_eGType;
    QWidget* m_QWidget;
    QPushButton* m_QPushButton;
    QTextEdit* m_QTextEdit;
    QSpinBox* m_QSpinBox;
    QSlider* m_QSlider;
    QVBoxLayout* m_QVBoxLayout;
    QHBoxLayout* m_QHBoxLayout;
};
//==============================================
#endif
//==============================================
