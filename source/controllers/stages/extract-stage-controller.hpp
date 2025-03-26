#ifndef EXTRACT_STAGE_CONTROLLER_HPP
#define EXTRACT_STAGE_CONTROLLER_HPP

#include <QObject>
#include <QString>
#include <controllers/base-controller.hpp>
#include <views/stages/extract-stage-screen.hpp>

class ExtractWorker;

class ExtractStageController final : public QObject,
                                     public BaseController<ExtractStageScreen> {
  Q_OBJECT
 public:
  explicit ExtractStageController(ExtractStageScreen* sub,
                                  QObject* parent = nullptr);
 signals:
  void finishExtract();
 public slots:
  void onPressExtractButton();

 private:
  void __finishExtract(bool result);
};

class ExtractWorker : public QObject {
  Q_OBJECT
 public:
  explicit ExtractWorker(QObject* parent = nullptr);
 public slots:
  void run();
 signals:
  void finish(bool result);
};

#endif  // EXTRACT_STAGE_CONTROLLER_HPP