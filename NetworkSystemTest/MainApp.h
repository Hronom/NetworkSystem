#ifndef MAINAPP_H
#define MAINAPP_H

#include <QObject>

class MainApp: public QObject
{
    Q_OBJECT

public:
    explicit MainApp(QObject *parent = 0);
    ~MainApp();

    void timerEvent(QTimerEvent *event);

private:
    void initServer();
    void initClient();

};

#endif // MAINAPP_H
