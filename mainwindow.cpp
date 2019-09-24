#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolButton>
#include <QShortcut>
#include <QBitmap>
#include <QStyle>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QSet>
#include <QProcess>

using namespace wup;

MainWindow::MainWindow(Params & params, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    iconSize = params.getInt("iconSize", 64);
    ui->setupUi(this);

    configureWindow(params);
    configureCloseOnEscape();
    configureActions(params);

//    auto iconFilepath = "/usr/share/virt-manager/icons/hicolor/48x48/actions/vm_import_wizard.png";

//    addButton("Button 1", iconFilepath, "q", 0, 0);
//    addButton("Button 2", iconFilepath, "w", 0, 1);
//    addButton("Button 3", iconFilepath, "e", 0, 2);
//    addButton("Button 4", iconFilepath, "r", 1, 0);
//    addButton("Button 5", iconFilepath, "t", 1, 1);
//    addButton("Button 6", iconFilepath, "y", 1, 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureWindow(Params &params)
{
    if (params.has("fullscreen"))
    {
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        setParent(nullptr);
        setAttribute(Qt::WA_NoSystemBackground, true);
        setAttribute(Qt::WA_TranslucentBackground, true);
    //    setAttribute(Qt::WA_PaintOnScreen);
        QMainWindow::showFullScreen();

        if (params.len("fullscreen"))
        {
            auto color = params.getString("fullscreen");
            this->setStyleSheet(QString("background-color: #") + color);
        }
    }
    else
    {
        setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);
        setParent(nullptr);
        setAttribute(Qt::WA_NoSystemBackground, true);
        setAttribute(Qt::WA_TranslucentBackground, true);
    }
}

void MainWindow::configureCloseOnEscape()
{
    auto s = new QShortcut(QKeySequence("Escape"), this);
    connect(s, &QShortcut::activated, [this]()
    {
        close();
    });
}

void MainWindow::changeEvent(QEvent * event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange && !this->isActiveWindow())
        close();
}

void MainWindow::configureActions(Params &params)
{
    QList<Action*> actions;
    const QString actionsFilepath = params.getString("actions");
    const int numCols = params.getInt("cols", 5);

    loadActions(actionsFilepath, actions);

    int i = 0;
    int j = 0;

    for (auto & a : actions)
    {
        addButton(a, i, j);

        ++j;

        if (j == numCols)
        {
            ++i;
            j = 0;
        }
    }
}

void MainWindow::loadActions(const QString actionsFilepath, QList<MainWindow::Action *> &actions)
{
    QString homeDir = QDir::homePath();
    QFileInfo info(actionsFilepath);
    QFile file(actionsFilepath);
    QSet<QString> shortcuts;

    QDir::setCurrent(info.path());

    if (!file.open(QIODevice::ReadOnly))
        error("Could not open actions file");

    int i = 0;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        auto cells = line.split(';');

        if (cells.size() != 4)
            error("Wrong number of cells in actions file at line", i);

        auto a = new Action();


        a->name = cells[0];
        a->iconFilepath = QString(cells[1]).replace("~", homeDir);
        a->shortcut = cells[2];
        a->cmd = QString(cells[3]).replace("~", homeDir);

        if (shortcuts.contains(a->shortcut))
            error("Shortcut mapped twice:", a->shortcut);

        actions.push_back(a);

        ++i;
    }
}

void MainWindow::addButton(const Action * a,
                           const int row,
                           const int col)
{
    // Get the icon
    QIcon * icon;

    if (a->iconFilepath.endsWith("svg"))
    {
        icon = new QIcon(a->iconFilepath);
    }
    else
    {
        QPixmap pixmap(a->iconFilepath);
        if (pixmap.width() != iconSize)
        {
            QPixmap scaled = pixmap.scaled( QSize(iconSize, iconSize), Qt::KeepAspectRatio, Qt::SmoothTransformation );
            icon = new QIcon(scaled);
        }
        else
        {
            icon = new QIcon(pixmap);
        }
    }



    // Configure the button
    auto b = new QToolButton();

    b->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    b->setIconSize(QSize(iconSize,iconSize));
    b->setIcon(*icon);
    b->setText(a->name + "\n(" + a->shortcut + ")");

    b->setStyleSheet(
                "QToolButton {"
                    "border: 0px;"
                    "border-radius: 6px;"
                    "background-color: #ff222222;"
                    "color: #fff;"
                    "padding-top: 7px;"
                    "padding-bottom: 6px;"
                    "padding-right: 20px;"
                    "padding-left: 20px;"
                "}"
                "QToolButton:hover {"
                    "background-color: #ff333333;"
                "}");

    // Callback to execute this action
    auto callback = [a, this]()
    {
//        QProcess::execute(a->cmd);

        QDir::setCurrent(QDir::homePath());
        QProcess::startDetached(a->cmd);
        close();
    };

    // Configure button click
    connect(b, &QToolButton::clicked, callback);

    // Configure shortcut
    auto s = new QShortcut(QKeySequence(a->shortcut), this);
    connect(s, &QShortcut::activated, callback);

    // Add button to screen
    ui->gridLayout->addWidget(b, row, col);
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
