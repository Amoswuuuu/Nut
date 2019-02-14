#ifndef TST_UPGRADES_H
#define TST_UPGRADES_H

#include <QObject>

namespace Nut {
class Database;
}
class Upgrades : public QObject
{
    Q_OBJECT

    void initDb(Nut::Database &db);

public:
    Upgrades();
    ~Upgrades();

private slots:
    void initTestCase();

    void version1();
    void version2();
    void version3();

};

#endif // TST_UPGRADES_H
