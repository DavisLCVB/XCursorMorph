#include "cursor-button-component.hpp"
#include "ui_cursor-button-component.h"

#include <QFileInfo>
#include <QStyle>
#include <QTimer>
#include <models/formats/animated-cursor.hpp>
#include <models/formats/static-cursor.hpp>
#include <models/state.hpp>

CursorButtonComponent::CursorButtonComponent(QWidget* parent)
    : QWidget(parent), ui(new Ui::CursorButtonComponent) {
  ui->setupUi(this);
  ui->IconLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->TextLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->widget->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->Content->setAttribute(Qt::WA_Hover);
  ui->IconLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
  ui->IconLabel->setStyleSheet("background: transparent;");
  ui->Content->setStyleSheet(__normalStyle);
  ui->Content->style()->unpolish(ui->Content);
  ui->Content->style()->polish(ui->Content);
}

CursorButtonComponent::~CursorButtonComponent() {
  delete ui;
}

void CursorButtonComponent::setIcon(const QString& icon) {
  try {
    const auto cacheDir = State::instance().cacheDirectory();
    const QString cacheImagePath =
        cacheDir + "/" + QFileInfo(icon).fileName() + ".cache.png";
    if (QFileInfo(cacheImagePath).exists()) {
      ui->IconLabel->setPixmap(QPixmap(cacheImagePath));
      ui->TextLabel->setText(QFileInfo(icon).fileName().split('.').first());
      return;
    }
    auto file = QFileInfo(icon);
    if (!file.exists()) {
      ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
      ui->TextLabel->setText(icon);
    }
    if (file.suffix() == "cur") {
      StaticCursor cursor = StaticCursor::fromPath(icon);
      cursor.entries().back().toPng(cacheImagePath);
      ui->IconLabel->setPixmap(QPixmap(cacheImagePath));
      ui->TextLabel->setText(file.fileName().split('.').first());
      return;
    }
    if (file.suffix() == "ani") {
      AnimatedCursor cursor = AnimatedCursor::fromPath(icon);
      cursor.frames().front().entries().back().toPng(cacheImagePath);
      ui->IconLabel->setPixmap(QPixmap(cacheImagePath));
      ui->TextLabel->setText(
          file.fileName().split('.').first().split('.').first());
      return;
    }
    ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
    ui->TextLabel->setText(file.fileName().split('.').first());
  } catch (...) {
    ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
    ui->TextLabel->setText(icon);
  }
}

void CursorButtonComponent::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    ui->Content->setStyleSheet(__pressedStyle);
    ui->Content->style()->unpolish(ui->Content);
    ui->Content->style()->polish(ui->Content);
    emit clicked();
    QTimer::singleShot(100, this, [this]() { resetStyle(); });
  }
  QWidget::mousePressEvent(event);
}

void CursorButtonComponent::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    ui->Content->setStyleSheet(__normalStyle);
    ui->Content->style()->unpolish(ui->Content);
    ui->Content->style()->polish(ui->Content);
  }
  QWidget::mouseReleaseEvent(event);
}

void CursorButtonComponent::resizeEvent(QResizeEvent* event) {
  const auto size = event->size();
  const auto width = size.width();
  const auto height = size.height();
  if (width < height) {
    const auto newHeight = width;
    setMinimumHeight(newHeight);
    setMaximumHeight(newHeight);
  } else {
    const auto newWidth = height;
    setMinimumWidth(newWidth);
    setMaximumWidth(newWidth);
  }
  QWidget::resizeEvent(event);
}

void CursorButtonComponent::resetStyle() {
  ui->Content->setStyleSheet(__normalStyle);
  ui->Content->style()->unpolish(ui->Content);
  ui->Content->style()->polish(ui->Content);
}

QString CursorButtonComponent::__pressedStyle =
    "QWidget#Content{"
    "  border: 1px solid;"
    "  border-color: #ffffff;"
    "  border-radius: 10px;"
    "  background-color: rgba(255, 255, 255, 20);"
    "}";

QString CursorButtonComponent::__normalStyle =
    "QWidget#Content{"
    "  border: 1px solid;"
    "  border-color: #ffffff;"
    "  border-radius: 10px;"
    "  background-color: rgba(255, 255, 255, 51);"
    "}"
    "QWidget#Content:hover{"
    "  border: 1px solid;"
    "  border-color: #ffffff;"
    "  border-radius: 10px;"
    "  background-color: rgba(255, 255, 255, 75);"
    "}";