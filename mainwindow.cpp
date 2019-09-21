#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <wup/wup.hpp>
#include <QToolButton>
#include <QShortcut>
#include <QBitmap>

using namespace wup;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showFullScreen();

    auto s = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")), this);

    connect(s, &QShortcut::activated, this, &MainWindow::on_shortcut);
    connect(s, &QShortcut::activated, []()
    {
        print("rocking");
    });

    auto iconFilepath = "/usr/share/virt-manager/icons/hicolor/48x48/actions/vm_import_wizard.png";

    addButton("Button 1", iconFilepath, "q", 0, 0);
    addButton("Button 2", iconFilepath, "w", 0, 1);
    addButton("Button 3", iconFilepath, "e", 0, 2);
    addButton("Button 4", iconFilepath, "r", 1, 0);
    addButton("Button 5", iconFilepath, "t", 1, 1);
    addButton("Button 6", iconFilepath, "y", 1, 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addButton(const char * const label,
                           const char * const iconFilepath,
                           const char * const shortcut,
                           const int row,
                           const int col)
{
    // Configure the button
    auto icon = new QIcon(iconFilepath);
    auto b = new QToolButton();

    b->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    b->setIconSize(QSize(64,64));
    b->setIcon(*icon);
    b->setText(label);

    ui->gridLayout->addWidget(b, row, col);

    // Configure shortcut
    auto s = new QShortcut(QKeySequence(shortcut), this);
    connect(s, &QShortcut::activated, [shortcut]()
    {
        print(shortcut);
    });
}

void MainWindow::on_actiona_triggered()
{
    print("a");
}

void MainWindow::on_actionb_triggered()
{
    print("b");
}

void MainWindow::on_shortcut()
{
    print("action");
}
