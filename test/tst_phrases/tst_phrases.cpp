#include <QtTest>
#include <QDate>

#include "tst_phrases.h"
#include "phrase.h"

using namespace Nut;

MainTest::MainTest(QObject *parent) : QObject(parent)
{
}

void MainTest::initTestCase()
{

}

void MainTest::no1()
{
    FieldPhrase<int> id("main", "id");
    FieldPhrase<QString> name("main", "name");
    FieldPhrase<QString> last_name("main", "last_name");
    FieldPhrase<QDate> date("main", "date");
    auto w = (id == 4 && name == "hi");
}

void MainTest::numeric()
{
    FieldPhrase<int> n("main", "int");

    auto p1 = n == 1;
    auto p2 = n <= 1;
    auto p3 = n >= 1;
    auto p4 = n < 1;
    auto p5 = n > 1;
    auto p6 = n != 1;
}

void MainTest::string()
{
    FieldPhrase<QString> str("main", "string");

    auto p1 = str == "salam";
    auto p2 = str.like("%hi%");
    auto p3 = str.isNull();
    auto p4 = str.in(QStringList() << "one" << "two" << "three");
    auto p5 = str != "hi" && str.like("%s");
}

void MainTest::boolean()
{
    FieldPhrase<bool> b("main", "bool");

    auto p1 = b;
    auto p2 = !b;
    auto p3 = b == false;

    QTEST_ASSERT(p1.data);
    QTEST_ASSERT(p2.data);
    QTEST_ASSERT(p3.data);
}

void MainTest::datetime()
{
    FieldPhrase<QTime> time("main", "time");
    FieldPhrase<QDate> date("main", "date");
    FieldPhrase<QDateTime> datetime("main", "datetime");

    auto p1 = time <= QTime::currentTime();
    auto p2 = time.addHours(2) < QTime::currentTime();
    auto p3 = date == QDate::currentDate();
    auto p4 = date.addDays(1) == QDate::currentDate();
    auto p5 = datetime > QDateTime::currentDateTime();
    auto p6 = datetime.addMonths(1) >= QDateTime::currentDateTime();
    auto p7 = time.between(QTime::currentTime().addSecs(-100), QTime::currentTime());
}

void MainTest::extra()
{
    FieldPhrase<QUrl> url("main", "url");

    auto p1 = url == QUrl();
    auto p2 = url == "http://google.com";
}

QTEST_MAIN(MainTest)
