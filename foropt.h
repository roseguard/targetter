#ifndef FOROPT
#define FOROPT

#include <QHostAddress>

struct optSaver
{
    QHostAddress    addr;
    int             port;
    QString         name;
    int             music;
    int             effects;
};

struct fieldsTypes
{
    const int iceField = 0;
    const int technick = 1;
};

#endif // FOROPT

