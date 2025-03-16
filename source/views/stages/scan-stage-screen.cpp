#include "scan-stage-screen.hpp"
#include "ui_scan-stage-screen.h"

#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QGridLayout>
#include <QRect>
#include <views/components/cursor-button-component.hpp>
#include <views/components/overlay-component.hpp>
#include <views/main-window.hpp>
#include <views/screens/cursor-dialog.hpp>
#include <views/utils/colors.hpp>

ScanStageScreen::ScanStageScreen(QWidget* parent)
    : QWidget(parent), ui(new Ui::ScanStageScreen) {
  ui->setupUi(this);
  QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
  shadow->setBlurRadius(5);
  shadow->setOffset(0, 4);
  shadow->setColor(Colors::buttonColor);
  ui->ScanButton->setGraphicsEffect(shadow);
  __layout = new QGridLayout(ui->CursorsContainer);
  ui->CursorsContainer->setLayout(__layout);
}

ScanStageScreen::~ScanStageScreen() {
  delete ui;
  if (__movie) {
    __movie->deleteLater();
  }
}

QPushButton* ScanStageScreen::ScanButton() const {
  return ui->ScanButton;
}

QWidget* ScanStageScreen::CursorsContainer() const {
  return ui->CursorsContainer;
}

void ScanStageScreen::setCursors(const QVector<QString>& cursors) {
  __cursors = cursors;
  const QString text =
      QString("Found <span style=\"color: %1\">%2</span> cursors")
          .arg(Colors::buttonColor.name())
          .arg(cursors.size());
  ui->CountCursorLabel->setText(text);
  __fillGrid(width());
}

void ScanStageScreen::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  __fillGrid(event->size().width());
}

void ScanStageScreen::__fillGrid(i32 width) {
  if (!__layout)
    return;
  if (!ui->CursorsContainer)
    return;
  const auto columns = 4;
  auto iconWidth = (width - 300) / columns;
  auto spacing = 0.3 * iconWidth;
  const auto gridWidth = columns * iconWidth + (columns - 1) * spacing;
  if (gridWidth > ui->CursorsContainer->width()) {
    iconWidth =
        (ui->CursorsContainer->width() - (columns - 1) * spacing) / columns;
    spacing = 0.3 * iconWidth;
  }
  for (auto index{0}; index < columns; ++index) {
    __layout->setColumnMinimumWidth(index, iconWidth);
    __layout->setColumnStretch(index, 1);
  }
  __layout->setSpacing(0.3 * iconWidth);
  //clean the layout
  QLayoutItem* item;
  item = __layout->takeAt(0);
  while (item) {
    if (item->widget()) {
      item->widget()->deleteLater();
    }
    delete item;
    item = __layout->takeAt(0);
  }
  for (auto index{0}; index < __cursors.size(); ++index) {
    auto button = new CursorButtonComponent(ui->CursorsContainer);
    button->setIcon(__cursors[index]);
    button->setMaximumHeight(iconWidth);
    button->setMinimumHeight(iconWidth);
    button->setMaximumWidth(iconWidth);
    button->setMinimumWidth(iconWidth);
    connect(button, &CursorButtonComponent::clicked, this,
            [this, index] { onCursorButtonPressed(__cursors[index]); });
    __layout->addWidget(button, index / columns, index % columns);
  }
}

void ScanStageScreen::onCursorButtonPressed(const QString& cursor) {
  const MainWindow* mainWin = dynamic_cast<MainWindow*>(window());
  OverlayComponent* overlay = new OverlayComponent(mainWin->Central());
  overlay->raise();
  overlay->setGeometry(window()->geometry());
  CursorDialog* dialog = new CursorDialog();
  dialog->setCursor(cursor);
  QRect dialogG = dialog->frameGeometry();
  QRect windowG = window()->geometry();
  dialog->move(windowG.center() - dialogG.center());
  overlay->move(windowG.topLeft());
  dialog->Header()->setTitle("Cursor Information");
  connect(dialog, &CursorDialog::finished, window(),
          [this, overlay] { overlay->hide(); });
  overlay->show();
  dialog->exec();
  overlay->deleteLater();
}

void ScanStageScreen::onScanButtonPressed() {
  if (__movie) {
    __movie->stop();
    __movie->deleteLater();
    __movie = nullptr;
  }
  __movie = new QMovie(":/gif/scan:white:anim");
  ui->ScanButton->setIconSize(QSize(16, 16));
  connect(__movie, &QMovie::frameChanged, ui->ScanButton, [this]() {
    ui->ScanButton->setIcon(QIcon(__movie->currentPixmap()));
  });
  if (__movie) {
    __movie->start();
  }
  ui->ScanButton->setDisabled(true);
  ui->ScanButton->setText(" Scanning...");
}

void ScanStageScreen::resetScanButton() {
  if (__movie) {
    __movie->stop();
    __movie->deleteLater();
    __movie = nullptr;
  }
  ui->ScanButton->setIcon(QIcon(":/icons/scan:white"));
  ui->ScanButton->setText("Scan");
  ui->ScanButton->setDisabled(false);
}