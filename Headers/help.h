#ifndef HELPER_H
#define HELPER_H

#include <QWidget>
#include <QLabel>
#include <QLayout>

namespace Ui {
class help;
}

class help : public QWidget
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = nullptr);
    ~help();

private:
    Ui::help *ui;

    /*帮助界面参数代码*/
    bool helperOpened = false;
    QLabel *helperTitleLabel;
    QLabel *helperContentLabel;
    QVBoxLayout *helperQVBoxLayout;
};

#endif // HELPER_H
