#ifndef PRGUI_H
#define PRGUI_H

#include <QMainWindow>
#include <QMap>
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
private:
    std::string getStrKeyword(QString &key)const;
    QString getQstrKeyword(QString & key)const;
    void setKeywordMap();

    bool gui_saveFile(const QString &fileName);
    void gui_do_file_Open();
    bool gui_LoadFile();
    bool gui_do_file_Load(const QString &fileName);
    void gui_do_file_Save();
    void gui_do_file_SaveAs();
    void gui_do_file_SaveOrNot();
    void saveGeneralSetting(GenSetDialog * dialog);
    void updateMenus();
    void createMenus();
    void createActions();
    void createStatusBar();
    void createToolBars();
    void createButtons();
    void switchLayoutDirection();
    void setMainWindowSize();

    Ui::PRGUI *ui;

    QMenu   *fileMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;

    QToolBar *fileToolBar;

    QPushButton *btspecify;

    bool _modified_file;
    bool _saved_file;
    QString _curFileName;
    int i_sim_type, i_unit_type, i_porosity_type, i_start_day;
    QMap<QString, QString> keywordMap;
};

#endif // PRGUI_H
