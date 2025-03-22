#ifndef IENTRY_HPP
#define IENTRY_HPP

#include <QString>

class IEntry {
 public:
  virtual ~IEntry() = default;
  virtual void toPng(const QString& path) = 0;
};

#endif  // IENTRY_HPP