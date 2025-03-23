#ifndef CURSOR_DIALOG_HPP
#define CURSOR_DIALOG_HPP

#include <QDialog>
#include <QPixmap>
#include <QString>
#include <QTimer>
#include <QVector>
#include <models/animated-cursor.hpp>
#include <models/static-cursor.hpp>
#include <types.hpp>
#include <views/components/header-component.hpp>

namespace Ui {
class CursorDialog;
}

class CursorDialog : public QDialog {
  Q_OBJECT

 public:
  explicit CursorDialog(QWidget* parent = nullptr);
  ~CursorDialog();
  void setCursor(const QString& cursor);
  HeaderComponent* Header() const;

 private slots:
  void onCloseButtonPressed();

 private:
  Ui::CursorDialog* ui;
  void __setText(const QString& cursorPath);
  void __fillStaticCursor(const StaticCursor& cursor, const QString& fileName,
                          const u64 size);
  void __fillAnimatedCursor(const AnimatedCursor& cursor,
                            const QString& fileName, const u64 size);
  QVector<QPixmap> __pixmaps;
  i64 __currFrame{0};
  QTimer* __timer = nullptr;
};

#endif  // CURSOR_DIALOG_HPP
