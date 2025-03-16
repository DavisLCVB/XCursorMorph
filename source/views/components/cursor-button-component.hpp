#ifndef CURSOR_BUTTON_COMPONENT_HPP
#define CURSOR_BUTTON_COMPONENT_HPP

#include <QMap>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QString>
#include <QWidget>

namespace Ui {
class CursorButtonComponent;
}

class CursorButtonComponent : public QWidget {
  Q_OBJECT

 public:
  explicit CursorButtonComponent(QWidget* parent = nullptr);
  ~CursorButtonComponent();
  void setIcon(const QString& icon);
  void resetStyle();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;
 signals:
  void clicked();

 private:
  Ui::CursorButtonComponent* ui;
  static QString __pressedStyle;
  static QString __normalStyle;
};

#endif  // CURSOR_BUTTON_COMPONENT_HPP
