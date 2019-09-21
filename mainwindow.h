#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    void addButton(const char * label, const char * iconFilepath, const char * shortcut, const int row, const int col);

private slots:
    void on_actiona_triggered();

    void on_actionb_triggered();

    void on_shortcut();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
