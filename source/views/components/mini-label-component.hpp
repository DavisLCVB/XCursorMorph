#ifndef MINI_LABEL_COMPONENT_HPP
#define MINI_LABEL_COMPONENT_HPP

#include <QString>
#include <QWidget>

namespace Ui {
class MiniLabelComponent;
}

class MiniLabelComponent : public QWidget {
  Q_OBJECT

 public:
  explicit MiniLabelComponent(QWidget* parent = nullptr);
  ~MiniLabelComponent();
  void setText(const QString& text);

 private:
  Ui::MiniLabelComponent* ui;
};

#endif  // MINI_LABEL_COMPONENT_HPP
