#ifndef SCAN_STAGE_SCREEN_HPP
#define SCAN_STAGE_SCREEN_HPP

#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QVector>
#include <QWidget>
#include <types.hpp>

namespace Ui {
class ScanStageScreen;
}

class ScanStageScreen : public QWidget {
  Q_OBJECT

 public:
  explicit ScanStageScreen(QWidget* parent = nullptr);
  ~ScanStageScreen();
  QPushButton* ScanButton() const;
  QWidget* CursorsContainer() const;
  void setCursors(const QVector<QString>& cursors);

 protected:
  void resizeEvent(QResizeEvent* event) override;
 private slots:
  void onCursorButtonPressed(const QString& cursor);

 private:
  Ui::ScanStageScreen* ui;
  QVector<QString> __cursors;
  QGridLayout* __layout;
  void __fillGrid(i32 width);
};

#endif  // SCAN_STAGE_SCREEN_HPP
