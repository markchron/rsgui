#ifndef PRGUI_H
#define PRGUI_H

#include <QMainWindow>
#include <QPushButton>

class QAction;
class QMenu;

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

    void showResWindow();
private:
    void createMenus();
    void createActions();
    void createToolBars();
    void createButtons();
    void createStatusBar();
    void updateMenus();
    void switchLayoutDirection();

    Ui::PRGUI *ui;

    QMenu   *fileMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;

    QToolBar *fileToolBar;

    QPushButton *btspecify;

    bool _exist_file;
};

#endif // PRGUI_H
