#ifndef FILE_H
#define FILE_H
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class File
{
public:
    File(const QString& _file_path);
    static File* newFile(const QString& _file_path);
    QString getPath();
    QString getType();

private:
    QString type;
    QString file_path;
};

#endif // FILE_H
