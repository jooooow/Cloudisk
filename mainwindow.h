#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QLayout>
#include <QDebug>
#include <QPainter>
#include "file.h"

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

private:
    Ui::MainWindow *ui;
    QStringList* path_list;
    QWidget* main_widget;
    QVBoxLayout* layout;
    QHBoxLayout* new_layout;
    QList<File>* file_list;
};

#endif // MAINWINDOW_H
