#include "stage-button.hpp"
#include "ui_stage-button.h"

#include <QMouseEvent>
#include <QStyle>

QMap<StageButtonState, QString> StageButton::__containerStyle = {
    {StageButtonState::Undone,
     "QWidget#Content{"
     "  border: 1px solid;"
     "  border-color: #9a9a9a;"
     "  border-radius: 10px;"
     "  background-color: rgba(255, 255, 255, 51);"
     "}"
     "QWidget#Content:hover{}"},
    {StageButtonState::Done,
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
     "}"},
    {StageButtonState::Current,
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
     "}"}};

QString StageButton::__pressedStyle =
    "QWidget#Content{"
    "  border: 1px solid;"
    "  border-color: #ffffff;"
    "  border-radius: 10px;"
    "  background-color: rgba(255, 255, 255, 20);"
    "}";

QMap<StageButtonState, QString> StageButton::__textStyle = {
    {StageButtonState::Undone,
     "QLabel#TextLabel{"
     "  font-size: 20px;"
     "  padding-right: 5px;"
     "  color: #9a9a9a;"
     "}"},
    {StageButtonState::Done,
     "QLabel#TextLabel{"
     "  font-size: 20px;"
     "  padding-right: 5px;"
     "  color: #ffffff;"
     "}"},

    {StageButtonState::Current,
     "QLabel#TextLabel{"
     "  font-size: 20px;"
     "  padding-right: 5px;"
     "  color: #ffffff;"
     "}"}};

QMap<StageButtonState, QString> StageButton::__iconStyle = {
    {StageButtonState::Undone, ":/stages/undone"},
    {StageButtonState::Done, ":/stages/done"},
    {StageButtonState::Current, ":/stages/in-progress"}};

QMap<StageButtonState, QString> StageButton::__arrowStyle = {
    {StageButtonState::Undone, ":/icons/arrow:right:gray"},
    {StageButtonState::Done, ":/icons/arrow:right:white"},
    {StageButtonState::Current, ":/icons/arrow:right:white"}};

StageButton::StageButton(QWidget* parent)
    : QWidget(parent), ui(new Ui::StageButton) {
  ui->setupUi(this);
  ui->TextLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->ArrowLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->IconLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->widget->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui->widget_2->setAttribute(Qt::WA_TransparentForMouseEvents);
  setMinimumSize(0, 40);
  setMaximumSize(16777215, 75);
  ui->IconLabel->setMaximumSize(25, 25);
  ui->ArrowLabel->setMaximumSize(25, 25);
  ui->Content->setAttribute(Qt::WA_Hover);
  setState(StageButtonState::Undone);
  ui->Content->setProperty("pressed", false);
}

StageButton::~StageButton() {
  delete ui;
}

void StageButton::setState(StageButtonState state) {
  __state = state;
  ui->Content->setStyleSheet(__containerStyle[state]);
  ui->TextLabel->setStyleSheet(__textStyle[state]);
  ui->IconLabel->setPixmap(QPixmap(__iconStyle[state]));
  ui->ArrowLabel->setPixmap(QPixmap(__arrowStyle[state]));
}

StageButtonState StageButton::state() const {
  return __state;
}

void StageButton::setText(const QString& text) {
  ui->TextLabel->setText(text);
}

QString StageButton::text() const {
  return ui->TextLabel->text();
}

void StageButton::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton &&
      __state != StageButtonState::Undone) {
    ui->Content->setStyleSheet(__pressedStyle);
    ui->Content->style()->unpolish(ui->Content);
    ui->Content->style()->polish(ui->Content);
  }
  QWidget::mousePressEvent(event);
}

void StageButton::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    ui->Content->setStyleSheet(__containerStyle[__state]);
    ui->Content->style()->unpolish(ui->Content);
    ui->Content->style()->polish(ui->Content);
  }
  QWidget::mouseReleaseEvent(event);
}