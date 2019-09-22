#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wup/wup.hpp>
#include <QMainWindow>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct Action
    {
        QString name;
        QString iconFilepath;
        QString shortcut;
        QString cmd;
    };

public:

    MainWindow(wup::Params & params, QWidget *parent = nullptr);
    ~MainWindow();

private:

    void configureWindow(wup::Params & params);

    void configureCloseOnEscape();

    void configureActions(wup::Params & params);

    void loadActions(const QString actionsFilepath, QList<Action*> & actions);

    void addButton(const Action * a, const int row, const int col);

    virtual void changeEvent(QEvent *event);

private slots:

    void on_actiona_triggered();

    void on_actionb_triggered();

    void on_shortcut();

private:

    Ui::MainWindow *ui;

    int iconSize;

};
#endif // MAINWINDOW_H
