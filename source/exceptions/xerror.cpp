#include "xerror.hpp"
#include <QDebug>

QMap<XErrorType, QString> XError::__typeMap = {
    {XErrorType::FileNotFound, "FileNotFound"},
    {XErrorType::FileNotOpened, "FileNotOpened"},
    {XErrorType::Unknown, "Unknown"},
    {XErrorType::InvalidData, "InvalidData"},
    {XErrorType::NotSupported, "NotSupported"},
    {XErrorType::CreationFailed, "CreationFailed"},
    {XErrorType::ReadError, "ReadError"},
};

XError::XError() : XError(__typeMap[XErrorType::Unknown]) {}

XError::XError(const QString& message) : XError(XErrorType::Unknown, message) {}

XError::XError(XErrorType type, const QString& message)
    : __message(message), __type(type) {}

QString XError::message() const {
  return __message;
}

XErrorType XError::type() const {
  return __type;
}

void XError::printFormated() const {
  const QString red("\033[1;31m");
  const QString reset("\033[0m");

  QString formattedMessage = QString("[%1%2 Error]: %3%4")
                                 .arg(red)
                                 .arg(__typeMap[__type])
                                 .arg(__message)
                                 .arg(reset);
  qCritical().noquote() << formattedMessage;
}

XError XError::invalidData(const QString& att, const QString& be,
                           const QString& toBe) {
  QString message = QString("Invalid data, %1: %2").arg(att).arg(be);
  if (!toBe.isEmpty()) {
    message.append(QString(", should be: %1").arg(toBe));
  }
  return XError(XErrorType::InvalidData, message);
}

XError XError::notSupported(const QString& msg) {
  return XError(XErrorType::NotSupported, msg);
}