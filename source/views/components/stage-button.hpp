#ifndef STAGE_BUTTON_HPP
#define STAGE_BUTTON_HPP

#include <QWidget>

namespace Ui {
class StageButton;
}

enum class StageButtonState { Undone, Done, Current };

class StageButton : public QWidget {
  Q_OBJECT

 public:
  explicit StageButton(QWidget* parent = nullptr);
  ~StageButton();
  void setState(StageButtonState state);
  StageButtonState state() const;
  void setText(const QString& text);
  QString text() const;

 private:
  Ui::StageButton* ui;
  StageButtonState __state;
  static QMap<StageButtonState, QString> __containerStyle;
  static QMap<StageButtonState, QString> __textStyle;
  static QMap<StageButtonState, QString> __iconStyle;
  static QMap<StageButtonState, QString> __arrowStyle;
};

#endif  // STAGE_BUTTON_HPP
