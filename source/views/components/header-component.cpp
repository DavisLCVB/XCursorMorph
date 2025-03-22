#include "header-component.hpp"
#include "ui_header-component.h"

HeaderComponent::HeaderComponent(QWidget* parent, QWidget* window)
    : QWidget(parent), ui(new Ui::HeaderComponent), __window(window) {
  ui->setupUi(this);
  ui->TitleLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
  ui->IconLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

HeaderComponent::~HeaderComponent() {
  delete ui;
}

void HeaderComponent::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    __isMooving = true;
    __lastPosition = event->globalPosition().toPoint() - __window->pos();
  }
}

void HeaderComponent::mouseMoveEvent(QMouseEvent* event) {
  if (__isMooving && (event->buttons() && Qt::LeftButton)) {
    __window->move(event->globalPosition().toPoint() - __lastPosition);
    event->accept();
  }
}

void HeaderComponent::mouseReleaseEvent(QMouseEvent* event) {
  __isMooving = false;
  event->accept();
}

void HeaderComponent::setTitle(const QString& title) {
  ui->TitleLabel->setText(title);
}

void HeaderComponent::setIcon(const QString& icon) {
  ui->IconLabel->setPixmap(QPixmap(icon));
}

void HeaderComponent::setWindow(QWidget* window) {
  __window = window;
}