#ifndef BASE_CONTROLLER_HPP
#define BASE_CONTROLLER_HPP

template <typename Widget>
class BaseController {
 public:
  BaseController(Widget* widget) : __widget(widget) {}

  virtual ~BaseController() = default;

 private:
  Widget* __widget;
};

#endif  // BASE_CONTROLLER_HPP