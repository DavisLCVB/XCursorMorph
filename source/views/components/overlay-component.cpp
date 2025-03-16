#include "overlay-component.hpp"

OverlayComponent::OverlayComponent(QWidget* parent) : QWidget(parent) {
  setAttribute(Qt::WA_TransparentForMouseEvents, false);
  setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
  setAttribute(Qt::WA_StyledBackground, true);
  setStyleSheet("background-color: rgba(0, 0, 0, 150); border-radius: 20px;");
}

void OverlayComponent::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  if (parentWidget()) {
    setGeometry(parentWidget()->geometry());
  }
}