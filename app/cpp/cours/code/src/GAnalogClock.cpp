//===============================================
#include "GAnalogClock.h"
//===============================================
GAnalogClock::GAnalogClock(QWidget* parent) : GQtUi(parent) {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onEvent()));
    timer->start(1000);
}
//===============================================
GAnalogClock::~GAnalogClock() {

}
//===============================================
void GAnalogClock::resize() {
    QFrame::resize(400, 350);
}
//===============================================
void GAnalogClock::paintEvent(QPaintEvent* event) {
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };
    static const QPoint secondeHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -90)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);
    QColor secondeColor(127, 127, 0, 191);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0) {
            painter.drawLine(92, 0, 96, 0);
        }
        painter.rotate(6.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(secondeColor);

    painter.save();
    painter.rotate(6.0 * (time.second() % 60));
    painter.drawConvexPolygon(secondeHand, 3);
    painter.restore();
}
//===============================================
void GAnalogClock::onEvent() {
    update();
}
//===============================================
