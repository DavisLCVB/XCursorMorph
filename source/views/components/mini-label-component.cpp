#include "mini-label-component.hpp"
#include "ui_mini-label-component.h"

MiniLabelComponent::MiniLabelComponent(QWidget* parent)
    : QWidget(parent), ui(new Ui::MiniLabelComponent) {
  ui->setupUi(this);
}

MiniLabelComponent::~MiniLabelComponent() {
  delete ui;
}

void MiniLabelComponent::setText(const QString& text) {
  ui->TextLabel->setText(text);
}