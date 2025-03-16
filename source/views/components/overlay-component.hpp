#ifndef OVERLAY_COMPONENT_HPP
#define OVERLAY_COMPONENT_HPP

#include <QWidget>

class OverlayComponent final : public QWidget {
  Q_OBJECT

 public:
  explicit OverlayComponent(QWidget* parent = nullptr);

 protected:
  void resizeEvent(QResizeEvent* event) override;
};

#endif  // OVERLAY_COMPONENT_HPP