#include "extract-stage-screen.hpp"
#include "ui_extract-stage-screen.h"

#include <QString>
#include <models/state.hpp>

ExtractStageScreen::ExtractStageScreen(QWidget* parent)
    : QWidget(parent), ui(new Ui::ExtractStageScreen) {
  ui->setupUi(this);
  ui->ResultLabel->setText("");
}

ExtractStageScreen::~ExtractStageScreen() {
  delete ui;
}

void ExtractStageScreen::setResult(bool result) {
  if (result) {
    const auto buildDir = State::instance().buildDirectory();
    qDebug() << "Build directory: " << buildDir;
    ui->ResultLabel->setText(
        "<p><span style=\"font-weight:700;\">Success! </span><span "
        "style=\"font-weight:400;\">Files extracted in </span><span "
        "style=\"font-weight:400;text-decoration:underline;\">" +
        buildDir +
        "</span></"
        "p>");
  } else {
    ui->ResultLabel->setText(
        "<p><span style=\"font-weight:700;\">Failed!</span><span "
        "style=\"font-weight:400;\">Files extraction failed</span></p>");
  }
}

QPushButton* ExtractStageScreen::ExtractButton() {
  return ui->ExtractButton;
}