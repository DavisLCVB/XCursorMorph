#include "mini-label-container.hpp"
#include "ui_mini-label-container.h"

MiniLabelContainer::MiniLabelContainer(QWidget* parent)
    : QWidget(parent), ui(new Ui::MiniLabelContainer) {
  ui->setupUi(this);
  __layout = new QHBoxLayout(ui->MiniLabels);
  __layout->setContentsMargins(10, 0, 0, 0);
  __layout->setSpacing(10);
  ui->MiniLabels->setLayout(__layout);
}

MiniLabelContainer::~MiniLabelContainer() {
  delete ui;
}

void MiniLabelContainer::addMiniLabel(MiniLabelComponent* miniLabel) {
  __layout->addWidget(miniLabel);
}