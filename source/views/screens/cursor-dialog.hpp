#ifndef CURSOR_DIALOG_HPP
#define CURSOR_DIALOG_HPP

#include <QDialog>
#include <QString>
#include <models/formats/animated-cursor.hpp>
#include <models/formats/static-cursor.hpp>
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
};

#endif  // CURSOR_DIALOG_HPP
