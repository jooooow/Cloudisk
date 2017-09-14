#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    for(auto pic : pic_list)
        delete pic;
    for(auto box : hbox_list)
        delete box;
    delete ui;
}

void MainWindow::init()
{
    area = ui->scrollArea;
    main_widget = new QWidget(area);
    main_layout = new QVBoxLayout(main_widget);
    current_layout = nullptr;
    current_layout_index = 0;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    qDebug()<<"resize";
    if(path_list.isEmpty())
        return;
    if(area->width() < 140 + 10)
        return;
    if(col_count == area->width() / 140)
        return;
    int file_count = path_list.count();
    col_count = area->width() / 140;
    int row_count = file_count % col_count == 0 ? file_count / col_count : file_count / col_count + 1;
    qDebug()<<"col_count : "<<col_count<<" "<<"row_count : "<<row_count;

    current_layout = hbox_list.at(0);

    int list_count = hbox_list.count();

    if(current_layout->count() > col_count || list_count < row_count)
    {
        qDebug()<<"increase";
        if(list_count < row_count)
        {
            qDebug()<<"need add box";
            qDebug()<<current_layout->count()<<"-"<<list_count;
            int count = row_count - hbox_list.count();
            for(int i = 0; i < count; i++)
            {
                current_layout = new QHBoxLayout();
                main_layout->addLayout(current_layout);
                hbox_list.push_back(current_layout);
            }
        }

        int index = 0;
        current_layout = hbox_list.at(index);
        QList<QWidget*> fifo;
        for(int i = 0; i < row_count - 1; i++)
        {

            int count = current_layout->count();
            for(int j = 0; j < count - col_count; j++)
            {
                QWidget* lab = current_layout->takeAt(current_layout->count() - 1)->widget();
                fifo.push_back(lab);
                current_layout->removeWidget(lab);
            }
            current_layout = hbox_list.at(++index);
            int limit = fifo.count();
            for(int i = 0; i < limit; i++)
            {
                current_layout->insertWidget(0,fifo.at(0));
                fifo.pop_front();
            }
        }
    }

    else if((current_layout->count() < col_count || list_count > row_count) && path_list.count() >= col_count)
    {
        qDebug()<<"decrease";

        int index = 0;
        int next_index = 1;
        current_layout = hbox_list.at(index);
        QHBoxLayout* next = hbox_list.at(next_index);
        qDebug()<<hbox_list.count();
        while(index <= hbox_list.count() - 1)
        {
            qDebug()<<"*";
            qDebug()<<next->count();
            while(next->count() != 0 && current_layout->count() < col_count)
            {
                qDebug()<<"**";
                QWidget* pic = next->takeAt(0)->widget();
                next->removeWidget(pic);
                current_layout->addWidget(pic);
            }
            if(next_index >= hbox_list.count() - 1 && next->count() == 0) break;
            if(current_layout->count() == col_count)
            {
                qDebug()<<"****";
                current_layout = hbox_list.at(++index);
                if(index == hbox_list.count() - 1)
                    break;
                if(next_index == hbox_list.count() - 1)
                    next = hbox_list.at(next_index);
                else
                    next = hbox_list.at(++next_index);
            }
            else if(next->count() == 0)
            {
                qDebug()<<"***";
                if(next_index == hbox_list.count() - 1)
                    next = hbox_list.at(next_index);
                else
                    next = hbox_list.at(++next_index);
            }
            qDebug()<<"index : "<<index;
            qDebug()<<"next_index : "<<next_index;
        }

        if(list_count > row_count)
        {
            qDebug()<<"delete box";
            int count = main_layout->count() - row_count;
            QLayoutItem* child;
            int last = main_layout->count() - 1 - count;
            for(int i = main_layout->count() - 1; i > last; i--)
            {
                qDebug()<<main_layout->count();
                child = main_layout->takeAt(i);
                main_layout->removeItem(child);
                delete hbox_list.last();
                hbox_list.pop_back();
            }
        }
    }

    area->setWidget(main_widget);
    current_layout = hbox_list.at(0);
    qDebug()<<"current_layout->count() : "<<current_layout->count()
           <<"main_layout->count() : "<<main_layout->count();

}

void MainWindow::on_pushButton_clicked()
{
    resizeEvent(nullptr);
    current_list = QFileDialog::getOpenFileNames(this,"Select Files","F:/temp/test");
    if(current_list.isEmpty())
        return;
    path_list += current_list;
    qDebug()<<"path_list : "<<current_list<<"\n";
    qDebug()<<"all list : "<<path_list;

    int file_count = path_list.count();
    col_count = area->width() / 140;
    int row_count = file_count % col_count == 0 ? file_count / col_count : file_count / col_count + 1;
    qDebug()<<"col_count : "<<col_count<<" "<<"row_count : "<<row_count;

    if(hbox_list.count() < row_count)
    {
        qDebug()<<"need add box";
        int count = row_count - hbox_list.count();
        for(int i = 0; i < count; i++)
        {
            qDebug()<<"add layout";
            current_layout = new QHBoxLayout();
            main_layout->addLayout(current_layout);
            hbox_list.push_back(current_layout);
        }
    }
    current_layout = hbox_list.at(current_layout_index);

    for(auto f : current_list)
    {
        if(current_layout->count() == 0)
        {
            current_layout = hbox_list.at(current_layout_index);
        }
        else if(current_layout->count() == col_count)
        {
            current_layout = hbox_list.at(++current_layout_index);
        }
        QLabel* lab = new QLabel();
        QPixmap source("./images/psd.png");
        QPixmap icon(128,128);
        QPainter painter(&icon);
        painter.drawPixmap(0,0,128,128,source);
        lab->setPixmap(icon);
        current_layout->addWidget(lab);
                qDebug()<<"current_layout->count() : "<<current_layout->count();
    }
    area->setWidget(main_widget);
    qDebug()<<hbox_list.at(0)->count();
}

//void MainWindow::on_pushButton_2_clicked()
//{
//        int count = main_layout->count();
//        QLayoutItem* child;
//        for(int i = 0; i < count; i++)
//        {
//            child = main_layout->takeAt(main_layout->count() - 1);
//            main_layout->removeItem(child);
//            delete hbox_list.last();
//            hbox_list.pop_back();
//        }
//        path_list.clear();
//        qDebug()<<main_layout->count();
//}
