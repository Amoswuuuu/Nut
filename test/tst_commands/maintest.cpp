#include <QtTest>
#include <QJsonDocument>
#include <QSqlError>

#include "consts.h"

#include "maintest.h"
#include "query.h"
#include "tableset.h"
#include "tablemodel.h"
#include "databasemodel.h"

#include "post.h"
#include "comment.h"
#include "user.h"
#include "score.h"

MainTest::MainTest(QObject *parent) : QObject(parent)
{

}

void MainTest::initTestCase()
{
    qDebug() << "User type id:" << qRegisterMetaType<Post*>();
    qDebug() << "Comment type id:" << qRegisterMetaType<Comment*>();
    qDebug() << "DB type id:" << qRegisterMetaType<WeblogDatabase*>();

    db.setDriver(DRIVER);
    db.setHostName(HOST);
    db.setDatabaseName(DATABASE);
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);

    bool ok = db.open();

    QTEST_ASSERT(ok);
}

void MainTest::cmd1()
{
    Query<Post> *q = db.posts()->query()
            ->setWhere(Post::titleField() == "test" && Post::idField() < 4 + 5);

    q->toList();

    qDebug() << q->sqlCommand();
}

void MainTest::cmd2()
{
    Query<Post> *q = db.posts()->query()
            ->setWhere(!Post::idField().in({1, 2, 3, 4}));

    q->toList();
//    q->update(Post::idField()++);

    qDebug() << q->sqlCommand();
}

void MainTest::join()
{
    auto q = db.posts()->query()
            ->join<User>()
            ->toList();

}

QTEST_MAIN(MainTest)
