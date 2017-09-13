#ifndef ICON_H
#define ICON_H

#include <QObject>
#include <QLabel>

class Icon : public QLabel
{
    Q_OBJECT
public:
    Icon();
    Icon(const QString& str);
};

#endif // ICON_H
