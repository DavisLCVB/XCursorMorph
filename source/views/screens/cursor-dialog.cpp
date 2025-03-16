#include "cursor-dialog.hpp"
#include "ui_cursor-dialog.h"

#include <QFileInfo>
#include <models/state.hpp>

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
}

CursorDialog::~CursorDialog() {
  delete ui;
}

HeaderComponent* CursorDialog::Header() const {
  return ui->Header;
}

void CursorDialog::setCursor(const QString& cursor) {
  try {
    const auto cacheDir = State::instance().cacheDirectory();
    const QString cacheImagePath =
        cacheDir + "/" + QFileInfo(cursor).fileName() + ".cache.png";
    if (QFileInfo(cacheImagePath).exists() && !cursor.endsWith("ani")) {
      ui->IconLabel->setPixmap(QPixmap(cacheImagePath));
      __setText(cursor);
      return;
    }
    auto file = QFileInfo(cursor);
    if (!file.exists()) {
      ui->IconLabel->setPixmap(QPixmap(":/icons/fallback"));
      __setText(cursor);
      return;
    }
    if (file.suffix() == "cur") {
      StaticCursor s_cursor = StaticCursor::fromPath(cursor);
      s_cursor.entries().back().toPng(cacheImagePath);
      ui->IconLabel->setPixmap(QPixmap(cacheImagePath));
      __setText(cursor);
      return;
    }
    if (file.suffix() == "ani") {
      AnimatedCursor a_cursor = AnimatedCursor::fromPath(cursor);
      const QString baseImagePath =
          cacheDir + "/" + a_cursor.name() + "/" + a_cursor.name() + ".";
      __pixmaps.clear();
      u64 index{0};
      for (const auto& frame : a_cursor.frames()) {
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
    StaticCursor cursor = StaticCursor::fromPath(cursorPath);
    __fillStaticCursor(cursor, fileName, fileSize);
  }
  if (suffix == "ani") {
    AnimatedCursor cursor = AnimatedCursor::fromPath(cursorPath);
    __fillStaticCursor(cursor.frames().front(), fileName, fileSize);
    ui->Frames->setText(QString("Frames: %1").arg(cursor.frames().size()));
  }
}

void CursorDialog::__fillStaticCursor(const StaticCursor& cursor,
                                      const QString& fileName, const u64 size) {
  ui->Name->setText(fileName.split('.').first());
  const auto fileData = QString("File: %1 (%2 KB)").arg(fileName).arg(size);
  ui->File->setText(fileData);
  auto sizes = QString("Sizes: ");
  auto hotspots = QString("Hotspots: ");
  auto bpps = QString("BPPs: ");
  for (const auto& entry : cursor.entries()) {
    sizes.append(QString("%1x%2, ").arg(entry.width()).arg(entry.height()));
    hotspots.append(
        QString("%1x%2, ").arg(entry.hotspotX()).arg(entry.hotspotY()));
    bpps.append(QString("%1, ").arg(entry.bytesPerPixel()));
  }
  sizes.chop(2);
  hotspots.chop(2);
  bpps.chop(2);
  ui->Sizes->setText(sizes);
  ui->Hotspots->setText(hotspots);
  ui->Bpps->setText(bpps);
  ui->Frames->setText("");
}

void CursorDialog::onCloseButtonPressed() {
  close();
}