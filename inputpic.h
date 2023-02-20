#ifndef INPUTPIC_H
#define INPUTPIC_H

#include <QWidget>

namespace Ui {
class inputPic;
}

class inputPic : public QWidget
{
    Q_OBJECT

public:
    explicit inputPic(QWidget *parent = nullptr);
    ~inputPic();

private:
    Ui::inputPic *ui;
};

#endif // INPUTPIC_H
