#ifndef XERROR_HPP
#define XERROR_HPP

#include <QMap>
#include <QString>

enum class XErrorType {
  FileNotFound,
  FileNotOpened,
  InvalidData,
  NotSupported,
  CreationFailed,
  ReadError,
  Unknown,
};

class XError {
 public:
  explicit XError(const QString& message);
  XError(XErrorType type, const QString& message);
  XError();
  QString message() const;
  XErrorType type() const;
  void printFormated() const;
  static XError invalidData(const QString& att, const QString& be,
                            const QString& toBe = "");
  static XError notSupported(const QString& msg);

 private:
  static QMap<XErrorType, QString> __typeMap;
  QString __message;
  XErrorType __type;
};

#endif  // XERROR_HPP