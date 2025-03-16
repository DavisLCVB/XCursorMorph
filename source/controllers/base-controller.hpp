#ifndef BASE_CONTROLLER_HPP
#define BASE_CONTROLLER_HPP

class IBaseController {
 public:
  virtual ~IBaseController() = default;
};

template <typename Widget>
class BaseController : public IBaseController {
 public:
  BaseController(Widget* widget) : __sub(widget) {}

  virtual ~BaseController() = default;

 protected:
  Widget* __sub;
};

#endif  // BASE_CONTROLLER_HPP