#ifndef MINI_LABEL_CONTAINER_HPP
#define MINI_LABEL_CONTAINER_HPP

#include <QHBoxLayout>
#include <QWidget>
#include <views/components/mini-label-component.hpp>

namespace Ui {
class MiniLabelContainer;
}

class MiniLabelContainer : public QWidget {
  Q_OBJECT

 public:
  explicit MiniLabelContainer(QWidget* parent = nullptr);
  ~MiniLabelContainer();
  void addMiniLabel(MiniLabelComponent* miniLabel);

 private:
  Ui::MiniLabelContainer* ui;
  QHBoxLayout* __layout = nullptr;
};

#endif  // MINI_LABEL_CONTAINER_HPP
