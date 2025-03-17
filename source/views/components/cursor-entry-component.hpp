#ifndef CURSOR_ENTRY_COMPONENT_HPP
#define CURSOR_ENTRY_COMPONENT_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QWidget>

namespace Ui {
class CursorEntryComponent;
}

class CursorEntryComponent : public QWidget {
  Q_OBJECT

 public:
  explicit CursorEntryComponent(QWidget* parent = nullptr);
  ~CursorEntryComponent();
  void setDataLabel(const QString& dataLabel);
  void setDataValue(const QString& dataValue);
  void setDataValue(QWidget* widget);

 private:
  Ui::CursorEntryComponent* ui;
  QLabel* __dataLabel = nullptr;
  QWidget* __dataWidget = nullptr;
  QHBoxLayout* __layout = nullptr;
  static QString __labelStyle;
};

#endif  // CURSOR_ENTRY_COMPONENT_HPP
