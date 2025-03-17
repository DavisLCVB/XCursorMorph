#include "cursor-entry-component.hpp"
#include "ui_cursor-entry-component.h"

CursorEntryComponent::CursorEntryComponent(QWidget* parent)
    : QWidget(parent), ui(new Ui::CursorEntryComponent) {
  ui->setupUi(this);
  __layout = new QHBoxLayout(ui->DataValue);
  __layout->setContentsMargins(0, 0, 0, 0);
  __layout->setSpacing(0);
  ui->DataValue->setLayout(__layout);
}

CursorEntryComponent::~CursorEntryComponent() {
  delete ui;
}

void CursorEntryComponent::setDataLabel(const QString& dataLabel) {
  ui->DataLabel->setText(dataLabel);
}

void CursorEntryComponent::setDataValue(const QString& dataValue) {
  if (__dataLabel) {
    __dataLabel->deleteLater();
    __dataLabel = nullptr;
  }
  if (__dataWidget) {
    __dataWidget->deleteLater();
    __dataWidget = nullptr;
  }
  __dataLabel = new QLabel(ui->DataValue);
  __dataLabel->setText(dataValue);
  __dataLabel->setStyleSheet(__labelStyle);
  __layout->addWidget(__dataLabel);
}

void CursorEntryComponent::setDataValue(QWidget* widget) {
  if (__dataLabel) {
    __dataLabel->deleteLater();
    __dataLabel = nullptr;
  }
  if (__dataWidget) {
    __dataWidget->deleteLater();
    __dataWidget = nullptr;
  }
  __dataWidget = widget;
  __layout->addWidget(__dataWidget);
}

QString CursorEntryComponent::__labelStyle =
    "QLabel {padding-left: 10px; color: #ffffff; font-size: 12pt; }";