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
#include "icon.h"
#define WIDTH 140

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event = nullptr);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStringList current_list;
    QStringList all_list;
    QWidget* main_widget;
    QVBoxLayout* layout;
    QHBoxLayout* new_layout;
    QList<File>* file_list;
    int hcount;

private:
    void clearScrollArea();
    void showIcons(const QStringList& pathes);
};

#endif // MAINWINDOW_H
