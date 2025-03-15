#include "header.hpp"
#include "ui_header.h"

Header::Header(QWidget* parent) : QWidget(parent), ui(new Ui::Header) {
  ui->setupUi(this);
  ui->TitleLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
  ui->IconLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

Header::~Header() {
  delete ui;
}

void Header::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    __isMooving = true;
    __lastPosition = event->globalPosition().toPoint() - window()->pos();
    setCursor(Qt::DragMoveCursor);
  }
}

void Header::mouseMoveEvent(QMouseEvent* event) {
  if (__isMooving && (event->buttons() && Qt::LeftButton)) {
    window()->move(event->globalPosition().toPoint() - __lastPosition);
    event->accept();
  }
}

void Header::mouseReleaseEvent(QMouseEvent* event) {
  __isMooving = false;
  event->accept();
  setCursor(Qt::ArrowCursor);
}