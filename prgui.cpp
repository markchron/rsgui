#include "prgui.h"
#include "ui_prgui.h"
#include <QMessageBox>

PRGUI::PRGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PRGUI)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->setWindowTitle(tr("Builder"));
    this->setUnifiedTitleAndToolBarOnMac(true);

    _exist_file = false;

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createButtons();

    updateMenus();
}

PRGUI::~PRGUI()
{
    delete ui;
}

void PRGUI:: showResWindow(){
    QMessageBox::warning(this, tr("Warning"), tr("showResWindow"), QMessageBox::Yes);
}

void PRGUI:: newFile(){

}
void PRGUI::open(){
    QMessageBox::warning(this, tr("Warning"), tr("openFile"), QMessageBox::Yes);
}
void PRGUI::save(){
    QMessageBox::warning(this, tr("Warning"), tr("save File"), QMessageBox::Yes);
}
void PRGUI::saveAs(){

}

void PRGUI::updateMenus(){
    saveAct->setEnabled(_exist_file);
    saveAsAct->setEnabled(_exist_file);
}

void PRGUI::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();

    fileMenu->addAction(exitAct);
}

void PRGUI::createActions(){
    newAct = new QAction(QIcon(":/icons/images/icon_new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/icons/images/icon_open.png"), tr("&Open..."), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered(bool)), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/icons/images/icon_save.png"),tr("&Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the data to disk"));
    connect(saveAct, SIGNAL(triggered(bool)), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered(bool)), qApp, SLOT(closeAllWindows()));
}
void PRGUI::createStatusBar(){
    statusBar()->showMessage(tr("Ready"));
}
void PRGUI::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
}
void PRGUI:: createButtons(){
    btspecify = new QPushButton(this);
    btspecify->setGeometry(QRect(0.6*width(), 0.2*height(), 100, 50));
    btspecify->setText("specify property");
    connect(btspecify, SIGNAL(clicked(bool)), this, SLOT(showResWindow()));
}
void PRGUI::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        qApp->setLayoutDirection(Qt::RightToLeft);
    else
        qApp->setLayoutDirection(Qt::LeftToRight);
}
