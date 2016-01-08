#ifndef PRGUI_H
#define PRGUI_H

#include <QMainWindow>
#include <QVector>
#include <QMap>

#include <QDockWidget>
#include <QCommandLinkButton>
#include <QListWidget>
#include "cartesiangriddialog.h"

class QPushButton;
class QAction;
class QMenu;
class QDialog;
class GenSetDialog;
class QCloseEvent;
class QTextStream;
class QString;

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

    Ui::PRGUI *ui;

    QMenu   * fileMenu;
    QMenu   * viewMenu;
    QMenu   * resrMenu;
    QMenu   * helpMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *createGridCartAct;

    QToolBar *fileToolBar;
    QToolBar *modeToolBar;

    QPushButton *btspecify;
    QListWidget *custmList;
    QCommandLinkButton *slotBts;


    bool _modified_file;
    bool _saved_file;
    QString _curFileName;
    int i_sim_type, i_unit_type, i_porosity_type, i_start_day;
    int i_grid_dim[3];

    QMap<QString, QString> keywordMap;
    QVector<QString> custmQueryVector;
};

#endif // PRGUI_H
