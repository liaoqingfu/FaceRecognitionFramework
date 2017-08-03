#ifndef TOP_H
#define TOP_H

#include <QWidget>
#include "pubheader.h"

namespace Ui {
class Top;
}

class Top : public QWidget
{
    Q_OBJECT

public:
    explicit Top(QWidget *parent = 0);
    ~Top();

private:
    Ui::Top *ui;
};

#endif // TOP_H
