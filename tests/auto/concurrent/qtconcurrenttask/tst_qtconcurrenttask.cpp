/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qtconcurrenttask.h>

#include <QtTest/QtTest>

class tst_QtConcurrentTask : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void taskWithFreeFunction();
    void taskWithClassMethod();
    void taskWithCallableObject();
    void taskWithLambda();
    void taskWithArguments();
    void useCustomThreadPool();
    void setPriority();
    void adjustAllSettings();
    void ignoreFutureResult();
};

using namespace QtConcurrent;

void tst_QtConcurrentTask::taskWithFreeFunction()
{
    QVariant value(42);

    auto result = task(&qvariant_cast<int>)
                      .withArguments(value)
                      .spawn()
                      .result();

    QCOMPARE(result, 42);
}
void tst_QtConcurrentTask::taskWithClassMethod()
{
    QString result("foobar");

    task(&QString::chop).withArguments(&result, 3).spawn().waitForFinished();

    QCOMPARE(result, "foo");
}
void tst_QtConcurrentTask::taskWithCallableObject()
{
    QCOMPARE(task(std::plus<int>())
                 .withArguments(40, 2)
                 .spawn()
                 .result(),
             42);
}

void tst_QtConcurrentTask::taskWithLambda()
{
    QCOMPARE(task([]{ return 42; }).spawn().result(), 42);
}

void tst_QtConcurrentTask::taskWithArguments()
{
    auto result = task([](int arg1, int arg2){ return arg1 + arg2; })
                      .withArguments(40, 2)
                      .spawn()
                      .result();
    QCOMPARE(result, 42);
}

void tst_QtConcurrentTask::useCustomThreadPool()
{
    QThreadPool pool;

    int result = 0;
    task([&]{ result = 42; }).onThreadPool(pool).spawn().waitForFinished();

    QCOMPARE(result, 42);
}

void tst_QtConcurrentTask::setPriority()
{
    QThreadPool pool;
    pool.setMaxThreadCount(1);

    QSemaphore sem;

    QVector<QFuture<void>> futureResults;
    futureResults << task([&]{ sem.acquire(); })
                         .onThreadPool(pool)
                         .spawn();

    const int tasksCount = 10;
    QVector<int> priorities(tasksCount);
    std::iota(priorities.begin(), priorities.end(), 1);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(priorities.begin(), priorities.end(), std::default_random_engine(seed));

    QVector<int> actual;
    for (int priority : priorities)
        futureResults << task([priority, &actual] { actual << priority; })
                             .onThreadPool(pool)
                             .withPriority(priority)
                             .spawn();

    sem.release();
    pool.waitForDone();

    for (const auto &f : futureResults)
        QVERIFY(f.isFinished());

    QVector<int> expected(priorities);
    std::sort(expected.begin(), expected.end(), std::greater<>());

    QCOMPARE(actual, expected);
}

void tst_QtConcurrentTask::adjustAllSettings()
{
    QThreadPool pool;
    pool.setMaxThreadCount(1);

    const int priority = 10;

    QVector<int> result;
    auto append = [&](auto &&...args){ (result << ... << args); };

    task(std::move(append))
        .withArguments(1, 2, 3)
        .onThreadPool(pool)
        .withPriority(priority)
        .spawn()
        .waitForFinished();

    QCOMPARE(result, QVector<int>({1, 2, 3}));
}
void tst_QtConcurrentTask::ignoreFutureResult()
{
    QThreadPool pool;

    std::atomic_int value = 0;
    for (std::size_t i = 0; i < 10; ++i)
        task([&value]{ ++value; })
            .onThreadPool(pool)
            .spawn(FutureResult::Ignore);

    pool.waitForDone();

    QCOMPARE(value, 10);
}

QTEST_MAIN(tst_QtConcurrentTask)
#include "tst_qtconcurrenttask.moc"
