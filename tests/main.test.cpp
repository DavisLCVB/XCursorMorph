#include <QtTest/QtTest>

class MainTest : public QObject {
  Q_OBJECT
 private slots:

  void test() { QVERIFY(1 == 1); }
};

int main(int argc, char** argv) {
  int status = 0;
  {
    MainTest tc;
    status = QTest::qExec(&tc, argc, argv);
  }
  return status;
}

#include "main.test.moc"