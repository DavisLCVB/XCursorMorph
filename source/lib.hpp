#pragma once
#ifndef XCURSOR_MORPH_LIB
#define XCURSOR_MORPH_LIB

#include <memory>
#include <types.hpp>

class XCursorMorph {
 public:
  static XCursorMorph& instance();
  i32 run(i32 argc, c8* argv[]);

  XCursorMorph(const XCursorMorph&) = delete;
  XCursorMorph& operator=(const XCursorMorph&) = delete;

  XCursorMorph(XCursorMorph&&) = delete;
  XCursorMorph& operator=(XCursorMorph&&) = delete;
  ~XCursorMorph() = default;

 protected:
  XCursorMorph() = default;

 private:
  void __loadResources();

 private:
  static std::unique_ptr<XCursorMorph> __instance;
};

#endif  // XCURSOR_MORPH_LIB