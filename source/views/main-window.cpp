#include "main-window.hpp"
#include "ui_main-window.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->ContentStack->setCurrentIndex(0);
  resize(1200, 800);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);
  ui->TitleLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
  ui->IconLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
  connect(ui->MinimizeButton, &QPushButton::clicked, this,
          &MainWindow::minimizeWindow);
  connect(ui->MaximizeButton, &QPushButton::clicked, this,
          &MainWindow::maximizeRestoreWindow);
  connect(ui->ExitButton, &QPushButton::clicked, this,
          &MainWindow::closeWindow);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::minimizeWindow() {
  showMinimized();
}

void MainWindow::maximizeRestoreWindow() {
  if (isMaximized()) {
    showNormal();
  } else {
    showMaximized();
  }
}

void MainWindow::closeWindow() {
  close();
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    __isMooving = true;
    __lastPosition =
        event->globalPosition().toPoint() - frameGeometry().topLeft();
    event->accept();
    setCursor(Qt::DragMoveCursor);
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
  if (__isMooving && (event->buttons() && Qt::LeftButton)) {
    move(event->globalPosition().toPoint() - __lastPosition);
    event->accept();
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
  __isMooving = false;
  event->accept();
  setCursor(Qt::ArrowCursor);
}