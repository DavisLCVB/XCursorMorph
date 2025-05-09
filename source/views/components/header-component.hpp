#ifndef HEADER_HPP
#define HEADER_HPP

#include <QMouseEvent>
#include <QPoint>
#include <QWidget>

namespace Ui {
class HeaderComponent;
}

class HeaderComponent : public QWidget {
  Q_OBJECT

 public:
  explicit HeaderComponent(QWidget* parent = nullptr,
                           QWidget* window = nullptr);
  ~HeaderComponent();
  void setTitle(const QString& title);
  void setIcon(const QString& icon);
  void setWindow(QWidget* window);

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;

 private:
  Ui::HeaderComponent* ui;
  bool __isMooving = false;
  QPoint __lastPosition;
  QWidget* __window = nullptr;
};

#endif  // HEADER_HPP
