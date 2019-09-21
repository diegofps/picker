#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolButton>
#include <QShortcut>
#include <QBitmap>
#include <QStyle>

using namespace wup;

MainWindow::MainWindow(Params & params, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (params.has("fullscreen"))
    {
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        setParent(0); // Create TopLevel-Widget
        setAttribute(Qt::WA_NoSystemBackground, true);
        setAttribute(Qt::WA_TranslucentBackground, true);
    //    setAttribute(Qt::WA_PaintOnScreen);
        QMainWindow::showFullScreen();
    }
    else
    {
        // Set attrib to prevent tiling
    }

    auto s = new QShortcut(QKeySequence("Escape"), this);

    connect(s, &QShortcut::activated, [this]()
    {
        this->close();
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

void MainWindow::addButton(const QString label,
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
    b->setText(label + "\n(" + shortcut + ")");

    b->setStyleSheet(
                "QToolButton {"
                    "border: 0px;"
                    "border-radius: 6px;"
                    "background-color: #aa000000;"
                    "color: #fff;"
                    "padding-top: 7px;"
                    "padding-bottom: 6px;"
                    "padding-right: 20px;"
                    "padding-left: 20px;"
                "}"
                "QToolButton:hover {"
                    "background-color: #bb000000;"
                "}");

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
