#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QScrollArea>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

protected:
    void resizeEvent(QResizeEvent* event);

private:
    Ui::MainWindow *ui;
    QScrollArea* area;
    QStringList current_list;
    QStringList path_list;
    QWidget* main_widget;
    QVBoxLayout* main_layout;
    QHBoxLayout* current_layout;
    QList<QLabel*> pic_list;
    QList<QHBoxLayout*> hbox_list;
    int current_layout_index;
    int col_count;
    void init();
};

#endif // MAINWINDOW_H
