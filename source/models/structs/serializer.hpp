#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <QByteArray>
#include <QDataStream>
#include <tuple>

class Serializer {
 public:
  template <typename... Ts>
  using Tuple = std::tuple<Ts...>;

  template <typename... Ts>
  static QByteArray pack(const Tuple<Ts...>& tuple) {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    std::apply([&](const auto&... args) { ((stream << args), ...); }, tuple);
    return data;
  }

  template <typename... Ts>
  static Tuple<Ts...> unpack(const QByteArray& data) {
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    Tuple<Ts...> tuple;
    std::apply([&](auto&... args) { ((stream >> args), ...); }, tuple);
    return tuple;
  }

 private:
  Serializer() = delete;
};

#endif  // SERIALIZER_HPP