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
    hcount = 0;
}

MainWindow::~MainWindow()
{
    delete file_list;
    file_list = nullptr;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(current_list.isEmpty())
        return;
    if(hcount == ui->scrollArea->width() / WIDTH)
        return;
    if(ui->scrollArea->width() / WIDTH == 0)
        return;

    clearScrollArea();
    showIcons(all_list);
    hcount = ui->scrollArea->width() / WIDTH;
}

void MainWindow::on_pushButton_clicked()
{
    current_list = QFileDialog::getOpenFileNames(this,"Selecte Files","F:/temp/test");
    all_list += current_list;
    showIcons(current_list);
    hcount = ui->scrollArea->width() / WIDTH;
}

void MainWindow::clearScrollArea()
{
    QLayoutItem* child;
    QWidget* temp;
    while((child = layout->takeAt(0)) != 0)
    {
        QHBoxLayout* lyt = static_cast<QHBoxLayout*>(child);
        QLayoutItem* grandchild;
        while((grandchild = lyt->takeAt(0)) != 0)
        {
            temp = grandchild->widget();
            delete temp;
        }
        temp = child->widget();
        delete temp;
    }
    delete layout;
    layout = new QVBoxLayout(main_widget);
    delete new_layout;
    new_layout = nullptr;
}

void MainWindow::showIcons(const QStringList& pathes)
{
    for(const QString& f : pathes)
    {
        File file(f);
        if(new_layout == nullptr || new_layout->count() % (ui->scrollArea->width() / WIDTH) == 0)
        {
            new_layout = new QHBoxLayout();
            layout->addLayout(new_layout);
        }
        Icon* lab = new Icon();
        QPixmap source(QString("./images/" + file.getType() + ".png"));
        QPixmap icon(128,128);
        QPainter painter(&icon);
        painter.drawPixmap(0,0,128,128,source);
        lab->setPixmap(icon);
        new_layout->addWidget(lab);
        ui->scrollArea->setWidget(main_widget);
    }
}
