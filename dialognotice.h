#ifndef DIALOGNOTICE_H
#define DIALOGNOTICE_H

#include <QDialog>

namespace Ui {
class DialogNotice;
}

class DialogNotice : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNotice(QString text="",QWidget *parent = 0);

    ~DialogNotice();

private:
    Ui::DialogNotice *ui;
};

#endif // DIALOGNOTICE_H
