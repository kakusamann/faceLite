#ifndef WOLCOME_H
#define WOLCOME_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class wolcome;
}

class wolcome : public QWidget
{
    Q_OBJECT

public:
    explicit wolcome(QWidget *parent = nullptr);
    wolcome(QString welStr);
    ~wolcome();



private:
    Ui::wolcome *ui;

    QLabel *wolcomeTextLabel;           // 界面布局
    QVBoxLayout *welcomeVLayout;
};

#endif // WOLCOME_H
