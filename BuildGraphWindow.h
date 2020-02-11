#ifndef BUILDGRAPHWINDOW_H
#define BUILDGRAPHWINDOW_H

#include <QWidget>

namespace Ui {
class BuildGraphWindow;
}

class BuildGraphWindow : public QWidget
{
    Q_OBJECT

public:
    int t;

public:
    explicit BuildGraphWindow(QWidget *parent = 0);
    ~BuildGraphWindow();

private:
    Ui::BuildGraphWindow *ui;
};

#endif // BUILDGRAPHWINDOW_H
