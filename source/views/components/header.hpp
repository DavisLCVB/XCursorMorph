#ifndef HEADER_HPP
#define HEADER_HPP

#include <QMouseEvent>
#include <QPoint>
#include <QWidget>

namespace Ui {
class Header;
}

class Header : public QWidget {
  Q_OBJECT

 public:
  explicit Header(QWidget* parent = nullptr);
  ~Header();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;

 private:
  Ui::Header* ui;
  bool __isMooving = false;
  QPoint __lastPosition;
};

#endif  // HEADER_HPP
