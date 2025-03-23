#include "cursor-dialog.hpp"
#include "ui_cursor-dialog.h"

#include <QFileInfo>
#include <models/state.hpp>
#include <views/components/mini-label-component.hpp>
#include <views/components/mini-label-container.hpp>

CursorDialog::CursorDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::CursorDialog) {
  ui->setupUi(this);
  connect(ui->CloseButton, &QPushButton::clicked, this,
          &CursorDialog::onCloseButtonPressed);
  setAttribute(Qt::WA_TranslucentBackground);
  setWindowModality(Qt::ApplicationModal);
  setWindowFlags(Qt::FramelessWindowHint);
  setModal(true);
  ui->Header->setWindow(this);
  ui->Name->setDataLabel("Name: ");
  ui->File->setDataLabel("File: ");
  ui->Sizes->setDataLabel("Sizes: ");
  ui->Hotspots->setDataLabel("Hotspots: ");
  ui->Bpps->setDataLabel("Bits per Pixel: ");
  ui->Frames->setDataLabel("Frames: ");
}

CursorDialog::~CursorDialog() {
  delete ui;
}

HeaderComponent* CursorDialog::Header() const {
  return ui->Header;
}

void CursorDialog::setCursor(const QString& cursor) {
  try {
    auto file = QFileInfo(cursor);
    if (!file.exists()) {
      ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
      __setText(cursor);
      return;
    }
    if (file.suffix() == "cur") {
      QString cacheImagePath = StaticCursor::fromFile(cursor).getPrev();
      ui->IconLabel->setPixmap(QPixmap(cacheImagePath));
      __setText(cursor);
      return;
    }
    if (file.suffix() == "ani") {
      QVector<QString> paths = AnimatedCursor::fromFile(cursor).getPrev();
      __pixmaps.clear();
      for (const auto& path : paths) {
        __pixmaps.push_back(QPixmap(path));
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
      __setText(cursor);
      return;
    }
    ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
  } catch (...) {
    ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
  }
}

void CursorDialog::__setText(const QString& cursorPath) {
  const auto file = QFileInfo(cursorPath);
  if (!file.exists()) {
    return;
  }
  auto suffix = file.suffix();
  const QString fileName = file.fileName();
  const u64 fileSize = file.size() / 1024;
  if (suffix == "cur") {
    StaticCursor cursor = StaticCursor::fromFile(cursorPath);
    __fillStaticCursor(cursor, fileName, fileSize);
    ui->Frames->hide();
  }
  if (suffix == "ani") {
    AnimatedCursor cursor = AnimatedCursor::fromFile(cursorPath);
    __fillAnimatedCursor(cursor, fileName, fileSize);
  }
}

void CursorDialog::__fillStaticCursor(const StaticCursor& cursor,
                                      const QString& fileName, const u64 size) {
  const QString name = QString("%1").arg(fileName.split('.').first());
  const QString file = QString("%1 (%2 KB)").arg(fileName).arg(size);
  const QString bpps =
      QString("%1").arg(cursor.entries().front().bitsPerPixel());
  ui->Name->setDataValue(name);
  ui->File->setDataValue(file);
  ui->Bpps->setDataValue(bpps);
  auto widgetSize = new MiniLabelContainer(ui->Sizes);
  auto widgetHotspot = new MiniLabelContainer(ui->Hotspots);
  for (const auto& entry : cursor.entries()) {
    auto size = QString("%1x%2")
                    .arg(entry.dimension().first)
                    .arg(entry.dimension().second);
    auto hotspot =
        QString("%1x%2").arg(entry.hotspot().first).arg(entry.hotspot().second);
    auto sizeLabel = new MiniLabelComponent(widgetSize);
    auto hotspotLabel = new MiniLabelComponent(widgetHotspot);
    sizeLabel->setText(size);
    hotspotLabel->setText(hotspot);
    widgetSize->addMiniLabel(sizeLabel);
    widgetHotspot->addMiniLabel(hotspotLabel);
  }
  ui->Sizes->setDataValue(widgetSize);
  ui->Hotspots->setDataValue(widgetHotspot);
}

void CursorDialog::__fillAnimatedCursor(const AnimatedCursor& cursor,
                                        const QString& fileName,
                                        const u64 size) {
  const QString name = QString("%1").arg(fileName.split('.').first());
  const QString file = QString("%1 (%2 KB)").arg(fileName).arg(size);
  const QString bpps = QString("%1").arg(
      cursor.frames().front().entries().front().bitsPerPixel());
  ui->Name->setDataValue(name);
  ui->File->setDataValue(file);
  ui->Bpps->setDataValue(bpps);
  ui->Frames->setDataValue(QString::number(cursor.frames().size()));
  const auto fFrame = cursor.frames().front();
  auto widgetSize = new MiniLabelContainer(ui->Sizes);
  auto widgetHotspot = new MiniLabelContainer(ui->Hotspots);
  for (const auto& entry : fFrame.entries()) {
    auto size = QString("%1x%2")
                    .arg(entry.dimension().first)
                    .arg(entry.dimension().second);
    auto hotspot =
        QString("%1x%2").arg(entry.hotspot().first).arg(entry.hotspot().second);
    auto sizeLabel = new MiniLabelComponent(widgetSize);
    auto hotspotLabel = new MiniLabelComponent(widgetHotspot);
    sizeLabel->setText(size);
    hotspotLabel->setText(hotspot);
    widgetSize->addMiniLabel(sizeLabel);
    widgetHotspot->addMiniLabel(hotspotLabel);
  }
  ui->Sizes->setDataValue(widgetSize);
  ui->Hotspots->setDataValue(widgetHotspot);
}

void CursorDialog::onCloseButtonPressed() {
  close();
}
