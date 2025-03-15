#ifndef ICON_RATIO_HPP
#define ICON_RATIO_HPP

#include <QLabel>
#include <QWidget>
#include <types.hpp>

class IconRatio final : public QLabel {
  Q_OBJECT
 public:
  explicit IconRatio(QWidget* parent = nullptr, f32 ratio = 1.0f);
  ~IconRatio() = default;
  void setRatio(f32 ratio);

 protected:
  i32 heightForWidth(i32 width) const override;
  bool hasHeightForWidth() const override;
  void resizeEvent(QResizeEvent* event) override;

 private:
  f32 __ratio;
};

#endif  // ICON_RATIO_HPP