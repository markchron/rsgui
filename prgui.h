#ifndef PRGUI_H
#define PRGUI_H

#include <QMainWindow>
#include <QVector>
#include <QMap>

#include <QDockWidget>
#include <QTabWidget>
#include <QCommandLinkButton>
#include <QListWidget>
#include <QString>
#include "cartesiangriddialog.h"
#include "treeview.h"

class QPushButton;
class QAction;
class QMenu;
class QDialog;
class GenSetDialog;
class QCloseEvent;
class QTextStream;
namespace Ui {
class PRGUI;
}

class PRGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit PRGUI(QWidget *parent = 0);
    ~PRGUI();

private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void closeEvent(QCloseEvent* event);

    void showResWindow();
    void showCartesianGridDialog();
private:
    void saveNumsIntoTStream(QTextStream& out, int n, int* array);
    void saveNumsIntoTStream(QTextStream &out, int n, double *array);
    std::string getStrKeyword(QString &key)const;
    QString getQstrKeyword(QString & key)const;
    void setKeywordMap();
    void setCustmQuery();

    bool gui_saveFile(const QString &fileName);
    void gui_do_file_Open();
    bool gui_LoadFile();
    bool gui_do_file_Load(const QString &fileName);
    void gui_do_file_Save();
    void gui_do_file_SaveAs();
    void gui_do_file_SaveOrNot();

    void gui_gen_GridCartesian(CartesianGridDialog* mdialog);

    void saveGeneralSetting(GenSetDialog * dialog);

    void designWindow();
    void updateMenus();

    void createDockWindows();
    void createMenus();
    void createActions();
    void createStatusBar();
    void createToolBars();
    void createButtons();
    void switchLayoutDirection();
    void setMainWindowSize();

//    QString num2QStr(int n, int* arr)const;
//    QString num2QStr(int n, double* arr) const;

    Ui::PRGUI *ui;
    QDockWidget * leftQW;
    QTabWidget * rightQW;
    QListWidget *custmList;
    QCommandLinkButton *slotBts[2];
    TreeView *rsrTree;


    QMenu   * fileMenu;
    QMenu   * viewMenu;
    QMenu   * resrMenu;
    QMenu   * helpMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *genGridCartDiagAct;

    QToolBar *fileToolBar;
    QToolBar *modeToolBar;

    QPushButton *btspecify;




    bool _modified_file;
    bool _saved_file;
    QString _curFileName;
    int i_sim_type, i_unit_type, i_porosity_type, i_start_day;

    QString i_grid_type, i_grid_kdir;
    int i_grid_dim[3];
    double d_grid_origin[3];
    double d_grid_step[3];

    QMap<QString, QString> keywordMap;
    QVector<QString> custmQueryVector;
};

#endif // PRGUI_H
