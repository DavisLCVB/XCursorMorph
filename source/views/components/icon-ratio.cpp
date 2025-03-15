#include "icon-ratio.hpp"
#include <QDebug>
#include <QResizeEvent>

IconRatio::IconRatio(QWidget* parent, f32 ratio)
    : QLabel(parent), __ratio(ratio) {
  setScaledContents(true);
  setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
}

i32 IconRatio::heightForWidth(i32 width) const {
  return static_cast<i32>(width / __ratio);
}

bool IconRatio::hasHeightForWidth() const {
  return true;
}

void IconRatio::setRatio(f32 ratio) {
  __ratio = ratio;
}

void IconRatio::resizeEvent(QResizeEvent* event) {
  QLabel::resizeEvent(event);
  auto size = event->size();
  auto width = size.width();
  auto height = size.height();
  if (height > width / __ratio) {
    height = width / __ratio;
  } else {
    width = height * __ratio;
  }
  setMinimumHeight(height);
  setMaximumHeight(height);
  setMinimumWidth(width);
  setMaximumWidth(width);
}