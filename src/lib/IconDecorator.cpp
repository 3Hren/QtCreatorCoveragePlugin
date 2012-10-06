#include "IconDecorator.h"

#include <coreplugin/fileiconprovider.h>

#include <QHash>

QIcon IconDecorator::getIconByName(const QString &name)
{
    static QHash<QString, QIcon> icons;
    if (icons.isEmpty()) {
        icons.insert("Dir.Headers", createIcon(QStyle::SP_DirIcon, QIcon(":/icons/images/headers.png")));
        icons.insert("Dir.Sources", createIcon(QStyle::SP_DirIcon, QIcon(":/icons/images/sources.png")));
        icons.insert("Dir.Project", createIcon(QStyle::SP_DirIcon, QIcon(":/icons/images/qt_project.png")));
        icons.insert("Dir.Other", createIcon(QStyle::SP_DirIcon, QIcon()));
        icons.insert("File.Headers", createIcon(QStyle::SP_FileIcon, QIcon(":/icons/images/headers.png")));
        icons.insert("File.Sources", createIcon(QStyle::SP_FileIcon, QIcon(":/icons/images/sources.png")));
    }

    return icons.value(name);
}

QIcon IconDecorator::createIcon(const QStyle::StandardPixmap &prototype, const QIcon &decorator)
{
    static const QSize desiredSize = QSize(16, 16);
    const QPixmap pixmap = Core::FileIconProvider::overlayIcon(prototype, decorator, desiredSize);
    QIcon icon;
    icon.addPixmap(pixmap);
    return icon;
}
