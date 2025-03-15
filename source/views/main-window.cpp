#include "main-window.hpp"
#include "ui_main-window.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->ContentStack->setCurrentIndex(0);
  resize(1200, 800);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);
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

QStackedWidget* MainWindow::ContentStack() const {
  return ui->ContentStack;
}

SelectFolderScreen* MainWindow::SelectFolder() const {
  return ui->SelectFolder;
}

MainContentScreen* MainWindow::MainContent() const {
  return ui->MainContent;
}

HeaderComponent* MainWindow::Header() const {
  return ui->Header;
}