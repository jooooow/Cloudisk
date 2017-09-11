#include "file.h"

File::File(const QString &_file_path):file_path(_file_path)
{
    int count = file_path.indexOf('.');
    type = file_path.right(file_path.length() - count - 1);
}

File* File::newFile(const QString &_file_path)
{
    File* f = new File(_file_path);
    return f;
}

QString File::getPath()
{
    return file_path;
}

QString File::getType()
{
    return type;
}

