#include "prgui.h"
#include "ui_prgui.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopWidget>
#include "resprodialog.h"

PRGUI::PRGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PRGUI)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->setWindowTitle(tr("Builder"));
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setMainWindowSize();

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
   // QMessageBox::warning(this, tr("Warning"), tr("showResWindow"), QMessageBox::Yes);
//    QDialog *dialog = new QDialog(this);
    ResProDialog *dialog = new ResProDialog(this);
    // dialog pointer is released while close MainWindow,
    // but it will be released once the dialog is closed by the following command
//    dialog->setAttribute(Qt::WA_DeleteOnClose);
//    dialog->setWindowTitle("Reservoir property");
//    dialog->setGeometry(QRect(50,50, 0.615*width(), 0.385*height()));
    dialog->show();
}

void PRGUI:: newFile(){

}
void PRGUI::open(){
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),tr("."), tr("DAT Files (*.dat);; Text Files (*.txt);; Raw Files (*.raw);; All Files (*.*)"));

    if(!path.isEmpty()){
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox :: warning(this, tr("Open File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        _exist_file = true;
        QMessageBox::warning(this, tr("Warning"), tr("Open file"), QMessageBox::Yes);
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("No file is selected."));
    }
    this->updateMenus();
}
void PRGUI::save(){
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("DAT Files (*.dat);; All Files (*.*)"));

    if (!path.isEmpty()){
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write file"),
                                 tr("Cannot save file:\n%1").arg(path));
            return;
        }
        QMessageBox::warning(this, tr("Warning"), tr("save File"), QMessageBox::Yes);
        file.close();
    } else{
        QMessageBox :: warning(this, tr("Path"),
                               tr("No file is selected."));
    }
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

void PRGUI::setMainWindowSize(){
    QSize availableSize = qApp->desktop()->availableGeometry().size();
    QSize winSize(0.9*availableSize.width(), 0.9*availableSize.height());

    this->setGeometry(QStyle::alignedRect(
                          Qt::LeftToRight,
                          Qt::AlignCenter,
                          winSize,
                          qApp->desktop()->availableGeometry()
                          )
                      );

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

}
