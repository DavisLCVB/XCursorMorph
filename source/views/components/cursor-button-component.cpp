#include "cursor-button-component.hpp"
#include "ui_cursor-button-component.h"

#include <QFileInfo>
#include <QStyle>
#include <QTimer>
#include <exceptions/xerror.hpp>
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
    const QFileInfo file(icon);
    const QString baseName = file.fileName().split('.').first();
    const QString cacheImagePath =
        cacheDir + "/" + file.fileName() + ".cache.png";
    if (QFileInfo(cacheImagePath).exists() && !icon.endsWith("ani")) {
      ui->IconLabel->setPixmap(QPixmap(cacheImagePath));
      ui->TextLabel->setText(baseName);
      return;
    }
    if (!file.exists()) {
      ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
      ui->TextLabel->setText(icon);
      return;
    }
    if (file.suffix() == "cur") {
      StaticCursor cursor = StaticCursor::fromPath(icon);
      cursor.entries().back().toPng(cacheImagePath);
      ui->IconLabel->setPixmap(QPixmap(cacheImagePath));
      ui->TextLabel->setText(baseName);
      return;
    }
    if (file.suffix() == "ani") {
      AnimatedCursor cursor = AnimatedCursor::fromPath(icon);
      const QString baseImagePath =
          cacheDir + "/" + cursor.name() + "/" + cursor.name() + ".";
      __pixmaps.clear();
      u64 index{0};
      for (const auto& frame : cursor.frames()) {
        const QString pngPath = baseImagePath + QString::number(index) + ".png";
        frame.entries().back().toPng(pngPath);
        __pixmaps.push_back(QPixmap(pngPath));
        ++index;
      }
      if (__timer) {
        __timer->stop();
        delete __timer;
        __timer = nullptr;
      }
      __currFrame = 0;
      __timer = new QTimer(this);
      __timer->setInterval(50);
      connect(__timer, &QTimer::timeout, this, [this]() {
        ui->IconLabel->setPixmap(__pixmaps[__currFrame]);
        __currFrame = (__currFrame + 1) % __pixmaps.size();
      });
      __timer->start(50);
      ui->TextLabel->setText(baseName.split('.').first());
      return;
    }
    ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
    ui->TextLabel->setText(baseName);
  } catch (XError& e) {
    e.printFormated();
    ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
    ui->TextLabel->setText(icon);
  } catch (std::exception& e) {
    qDebug() << e.what();
    ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
    ui->TextLabel->setText(icon);
  } catch (...) {
    qDebug() << "Unknown error";
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
  ui->IconLabel->setMinimumSize(
      size - QSize(size.width() * 5 / 7, size.height() * 5 / 7));
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