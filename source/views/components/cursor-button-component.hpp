#ifndef CURSOR_BUTTON_COMPONENT_HPP
#define CURSOR_BUTTON_COMPONENT_HPP

#include <QMap>
#include <QMouseEvent>
#include <QPixmap>
#include <QResizeEvent>
#include <QSize>
#include <QString>
#include <QVector>
#include <QWidget>
#include <types.hpp>

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
  QVector<QPixmap> __pixmaps;
  QTimer* __timer = nullptr;
  i64 __currFrame{0};
};

#endif  // CURSOR_BUTTON_COMPONENT_HPP
