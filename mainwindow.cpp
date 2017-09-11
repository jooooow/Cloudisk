#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    main_widget = new QWidget(this);
    layout = new QVBoxLayout(main_widget);
    file_list = new QList<File>();
    new_layout = nullptr;
}

MainWindow::~MainWindow()
{
    path_list = nullptr;
    delete file_list;
    file_list = nullptr;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QStringList&& l = QFileDialog::getOpenFileNames(this,"Selecte Files","F:/temp/test");
    path_list = &l;
    for(QString& f : *path_list)
    {
        File file(f);
        if(new_layout == nullptr || new_layout->count() % 5 == 0)
        {
            new_layout = new QHBoxLayout();
            layout->addLayout(new_layout);
        }
        QLabel* lab = new QLabel();
        QPixmap source(QString("./images/" + file.getType() + ".png"));
        QPixmap icon(128,128);
        QPainter painter(&icon);
        painter.drawPixmap(0,0,128,128,source);
        lab->setPixmap(icon);
        new_layout->addWidget(lab);
        ui->scrollArea->setWidget(main_widget);
    }
}
