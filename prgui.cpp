#include "prgui.h"
#include "ui_prgui.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QTextStream>
#include <QVBoxLayout>


#include "resprodialog.h"
#include "gensetdialog.h"
#include "qcustomplot.h"

PRGUI::PRGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PRGUI)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
//    this->setWindowTitle(tr("Builder"));
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setMainWindowSize();

    _modified_file = false;
    _saved_file = true;
    _curFileName = tr("PRGUINew.dat");
    this->setWindowTitle(_curFileName);

    setKeywordMap();

    designWindow();


}

PRGUI::~PRGUI()
{
    delete ui;
}
void PRGUI:: showCartesianGridDialog(){
    CartesianGridDialog * mdialog = new CartesianGridDialog;
    if( mdialog->exec() == QDialog::Accepted) {
        gui_gen_GridCartesian(mdialog);
    }
    delete mdialog;
}

void PRGUI:: showResWindow(){
   // QMessageBox::warning(this, tr("Warning"), tr("showResWindow"), QMessageBox::Yes);
//    QDialog *dialog = new QDialog(this);
    ResProDialog *dialog = new ResProDialog(this);
    dialog->show();
}

void PRGUI:: newFile(){
    gui_do_file_SaveOrNot();

    GenSetDialog * mdialog = new GenSetDialog;
    if( mdialog->exec() == QDialog::Accepted) {
      saveGeneralSetting(mdialog);
      _modified_file = true;
      _saved_file = false;
      updateMenus();
    }
    delete mdialog;
}
void PRGUI::open(){
    gui_do_file_Open();
    this->updateMenus();
}
void PRGUI::save(){
    gui_do_file_Save();
}
void PRGUI::saveAs(){
    gui_do_file_SaveAs();
}
void PRGUI::closeEvent(QCloseEvent *event){
    if(_modified_file){ // file is modified
        QMessageBox box;
        box.setWindowTitle(tr("Warning"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("Save changes to ") + _curFileName + tr("?"));
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);

        int ret = box.exec();
        if(ret == QMessageBox :: Yes) {
            gui_do_file_Save();
            event->accept();
        } else if (ret == QMessageBox::No){
            event->accept();
        } else if (ret == QMessageBox::Cancel) {
            event->ignore();
        }
    } else {
        event->accept();
    }
}


void PRGUI::saveNumsIntoTStream(QTextStream &out, int n, int* array){
    for (int i=0; i<n; i++){
        out << array[i]<<"\t";
    }
    out << "\n";
    return;
}

void PRGUI:: saveNumsIntoTStream(QTextStream &out, int n, double *array){
    for(int i=0; i<n; i++){
        out<<array[i] <<"\t";
    }
    out << "\n";
    return;
}

std::string PRGUI::getStrKeyword(QString &key) const{
    return getQstrKeyword(key).toStdString();
}
QString PRGUI::getQstrKeyword(QString &key) const{
    if(keywordMap.contains(key)) {
        QMap<QString, QString>::const_iterator it = keywordMap.find(key);
        QString val = it.value()+tr(":\t");
        return val;
    } else {
        return ( tr("#$ unknown ")%key );
    }
}
void PRGUI::setKeywordMap(){
    keywordMap.insert(tr("i_sim_type"), tr("model"));
    keywordMap.insert("i_unit_type", "unit_index");
    keywordMap.insert("i_porosity_type", "Por_index");

    keywordMap.insert("i_grid_type", "grid");
    //todo, to make sure the RadioButtons have same text
    keywordMap.insert("Cartesian", "cart");
    keywordMap.insert("Corner Points", "corner point");
    keywordMap.insert("i_grid_kdir", "kdir");
    keywordMap.insert("Up", "up");
    keywordMap.insert("Down", "down");

    keywordMap.insert("i_grid_dim", "extents");
    keywordMap.insert("d_grid_origin", "origin");
    keywordMap.insert("d_grid_step","cellsize");
}
void PRGUI::setCustmQuery(){
    custmQueryVector<<"I/O control" <<"Reservoir" <<"PVT" <<"Rock-Fluid"<<"Numerical" <<"Initialize";
}

// return bool, since may be failed to save
bool PRGUI::gui_saveFile(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Save As"),
                             tr("Cannot save file %1:\n %2").arg(fileName).arg(file.errorString())
                             );
        return false;
    }
    QTextStream out(&file);

    out << getQstrKeyword(tr("i_unit_type")) << i_unit_type <<'\n';
    out << getQstrKeyword(tr("i_sim_type")).toUtf8() <<  i_sim_type <<"\n";
    out << getQstrKeyword(tr("i_porosity_type")) << i_porosity_type <<"\n";
    out << getQstrKeyword(tr("i_grid_type")) << getQstrKeyword(i_grid_type) <<"\n";
//    out << getQstrKeyword(tr("i_grid_kdir")) << getQstrKeyword(i_grid_kdir) <<"\n";
    out << getQstrKeyword(tr("i_grid_dim")) ; saveNumsIntoTStream(out, 3, i_grid_dim);
    out << getQstrKeyword(tr("d_grid_origin")); saveNumsIntoTStream(out, 3, d_grid_origin);
    out << getQstrKeyword(tr("d_grid_step")); saveNumsIntoTStream(out, 3, d_grid_step);

    _saved_file = true;
    _modified_file = false;
    _curFileName = QFileInfo(fileName).canonicalFilePath(); //获得文件的标准路径
    setWindowTitle(_curFileName);
    return true;
}
void PRGUI::gui_do_file_Open(){
    gui_do_file_SaveOrNot();
    QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Open File"),
                        tr("."),
                        tr("DAT Files (*.dat);; "
                        "Text Files (*.txt);; "
                         "Raw Files (*.raw);; "
                         "All Files (*.*)"));
    if(!fileName.isEmpty()){
        gui_do_file_Load(fileName);
    }
}
bool PRGUI:: gui_LoadFile(){
    //todo
    return true;
}

bool PRGUI:: gui_do_file_Load(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,
                             tr("Open File"),
                             tr("Can not open file %1:\n %2.").arg(fileName).arg(file.errorString())
                             );
        return false;
    }
    _curFileName=QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(_curFileName);

    return gui_LoadFile();
}

void PRGUI::gui_do_file_Save(){
    if(_saved_file){
        gui_saveFile(_curFileName);
    } else {
        gui_do_file_SaveAs();
    }
}
void PRGUI::gui_do_file_SaveAs(){
    QString fileName = QFileDialog::getSaveFileName(this,
                                         tr("Save As"),
                                         ".",
                                         tr("DAT Files (*.dat);; All Files (*.*)")
                                         );
    if(!fileName.isEmpty()) {
        gui_saveFile(fileName);
    }
}
void PRGUI::gui_do_file_SaveOrNot(){
    if(_modified_file){ // file is modified
        QMessageBox box;
        box.setWindowTitle(tr("Warning"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("Save changes to ") + _curFileName + tr("?"));
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        if(box.exec() == QMessageBox :: Yes)
            gui_do_file_Save();
    }
}
void PRGUI::gui_gen_GridCartesian(CartesianGridDialog * dialog){
    i_grid_dim[0] = dialog->getNi();
    i_grid_dim[1] = dialog->getNj();
    i_grid_dim[2] = dialog->getNk();

    d_grid_origin[0] = dialog->getX0();
    d_grid_origin[1] = dialog->getY0();
    d_grid_origin[2] = dialog->getZ0();

    d_grid_step[0] = dialog->getStepX();
    d_grid_step[1] = dialog->getStepY();
    d_grid_step[2] = dialog->getStepZ();

    i_grid_type = dialog->getGridType();
    i_grid_kdir = dialog->getKdir();
    return;
}

void PRGUI::saveGeneralSetting(GenSetDialog *dialog){
    i_sim_type       = dialog->getSimType();
    i_unit_type      = dialog->getUnitType();
    i_porosity_type  = dialog->getPorosityType();
    i_start_day      = dialog->getStartDay();
}

void PRGUI::designWindow(){
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    updateMenus();

//    QGridLayout * layout = new QGridLayout;
//    layout->addWidget(leftQW, 0, 0, 1, 1);
//    layout->addWidget(rightQW, 0, 1, -1, 1);
//    QHBoxLayout *layout = new QHBoxLayout;
//    layout->addWidget(leftQW);
//    layout->addWidget(rightQW);

//    centralWidget()->setLayout(layout);

    QSplitter * mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(leftQW);
    mainSplitter->addWidget(rightQW);
    mainSplitter->setStretchFactor(2,1);

    setCentralWidget(mainSplitter);
}

void PRGUI::updateMenus(){
    //todo
}


void PRGUI::createDockWindows(){
    setCustmQuery();

    leftQW = new QDockWidget (tr("Custom Process"), this);
    leftQW->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    leftQW->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    leftQW->setMaximumWidth(0.3*this->width());
    //QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    //spLeft.setHorizontalStretch(1);
    //leftQW->setSizePolicy(spLeft);

    slotBts[0] = new QCommandLinkButton(custmQueryVector.at(1), this);
    slotBts[0]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    slotBts[0]->setMenu(resrMenu);

    slotBts[1] = new QCommandLinkButton(custmQueryVector.at(2), this);
    slotBts[1]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    slotBts[1]->setMenu(fileMenu);

    rsrTree = new TreeView(leftQW);
//    rsrTree->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy:: Fixed));

    QVBoxLayout *slotVLyt = new QVBoxLayout;
    slotVLyt->addWidget(slotBts[0]);
    slotVLyt->addWidget(slotBts[1]);
    slotVLyt->addWidget(rsrTree);

    QWidget *widLayout = new QWidget;

    widLayout->setLayout(slotVLyt);
    leftQW->setWidget(widLayout);

    addDockWidget(Qt::LeftDockWidgetArea, leftQW);
    viewMenu->addAction(leftQW->toggleViewAction());

    rightQW = new QTabWidget(this);
    //rightQW = new QWidget (this);
    rightQW->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    //rightQW->sizePolicy().setHorizontalStretch(1);
    rightQW->addTab(new QCustomPlot, tr("2D-plot"));
    rightQW->addTab(new TreeView, tr("3D-display"));

}

void PRGUI::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();
    resrMenu = menuBar()->addMenu("Reservoir");
    resrMenu->addAction(genGridCartDiagAct);

    menuBar()->addSeparator();
    helpMenu = menuBar()->addMenu(tr("&Help"));

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


    genGridCartDiagAct = new QAction(tr("create Grid Cartesian"), this);
    genGridCartDiagAct->setStatusTip(tr("Create structure Cartesian grid or cylindrical grid"));
    connect(genGridCartDiagAct, SIGNAL(triggered(bool)), this, SLOT(showCartesianGridDialog()));
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

   // modeToolBar = addToolBar(tr("mode"));

}
void PRGUI:: createButtons(){
    btspecify = new QPushButton(this);
    btspecify->setGeometry(QRect(0.6*width(), 0.2*height(), 100, 50));

    btspecify->setText("specify property");
    connect(btspecify, SIGNAL(clicked(bool)), this, SLOT(showResWindow()));
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
void PRGUI::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        qApp->setLayoutDirection(Qt::RightToLeft);
    else
        qApp->setLayoutDirection(Qt::LeftToRight);
}
/*
QString PRGUI::num2QStr(int n, int* arr){
    QString rst = " ";
    for(int i=0; i<n; i++){
        rst+= QString::number(arr(i),10);
    }

    return rst;
}
QString PRGUI::num2QStr(int n, double* arr){
    QString rst=" ";
    for(int i=0; i<n; i++){
        rst = rst + QString::number(arr(i),10) + tr("\t");
    }
    return rst;
}
*/
