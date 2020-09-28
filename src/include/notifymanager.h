/*****************************************************************************
MIT License

Copyright (c) 2020 tyyyyyy0906

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#ifndef NOTIFYMANAGER_H
#define NOTIFYMANAGER_H

#include <QObject>
#include <QQueue>

#include "notify.h"

class NotifyManager : public QObject
{
    Q_OBJECT
public:
    explicit NotifyManager( QObject *parent = 0);

    ~NotifyManager();
    void notify(const QString &title, const QString &body, const QString &icon = ":/message.png", const QString url = "");
    void setMaxCount(int count);
    void setDisplayTime(int ms);

private:
    class NotifyData {
    public:
        NotifyData(const QString &icon, const QString &title,
                   const QString &body, const QString url) :
                   icon(icon),
                   title(title),
                   body(body),
                   url(url){}

        QString icon;
        QString title;
        QString body;
        QString url;
    };

    void rearrange();
    void showNext();

    QQueue<NotifyData> dataQueue;
    QList<Notify*> notifyList;
    int maxCount;
    int displayTime;
};

#endif // NOTIFYMANAGER_H
