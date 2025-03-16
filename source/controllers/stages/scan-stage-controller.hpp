#ifndef SCAN_STAGE_CONTROLLER_HPP
#define SCAN_STAGE_CONTROLLER_HPP

#include <QObject>
#include <QString>
#include <QVector>
#include <controllers/base-controller.hpp>
#include <views/stages/scan-stage-screen.hpp>

class ScanStageController final : public QObject,
                                  public BaseController<ScanStageScreen> {
  Q_OBJECT
 public:
  explicit ScanStageController(ScanStageScreen* sub, QObject* parent = nullptr);
 private slots:
  void onPressScanButton();

 private:
  void __finishScan(const QVector<QString>& cursors);
};

class ScanWorker : public QObject {
  Q_OBJECT
 public:
  explicit ScanWorker(QObject* parent = nullptr);
 public slots:
  void run();
 signals:
  void finish(const QVector<QString>& cursors);

 private:
  void __scanRecursive(QVector<QString>& cursorPaths,
                       const QString& currentPath, const QString& avoid);
};

#endif  // SCAN_STAGE_CONTROLLER_HPP