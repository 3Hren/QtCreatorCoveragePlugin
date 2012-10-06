#pragma once

#include <QIcon>
#include <QStyle>

class IconDecorator
{
public:
    enum DecoratorType {Header, Source, Other};
    static QIcon getIconByName(const QString &name);

private:
    static QIcon createIcon(const QStyle::StandardPixmap &prototype, const QIcon &decorator);
};
