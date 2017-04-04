// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_NATIVE_VIEW_H_
#define ATOM_BROWSER_NATIVE_VIEW_H_

#include <memory>

#include "ui/gfx/native_widget_types.h"
#include "third_party/skia/include/core/SkColor.h"

#include "atom/browser/api/trackable_object.h"
#include "native_mate/handle.h"

namespace gfx {
class Rect;
}

namespace mate {
class Dictionary;
}

namespace atom {

// Abstracts away the differences between a NSView on macOS and a Chromium
// views::View on other platforms.
//
// The API is very similar to views::View because we will want to get rid of
// this entirely and use views::View directly after Chromium switches to
// views::View on macOS.
class NativeView {
 public:
  virtual ~NativeView();

  static NativeView* Create(const mate::Dictionary& options);

  virtual gfx::NativeView GetView() = 0;

  virtual void AddChildView(NativeView* view) = 0;
  virtual void RemoveChildView(NativeView* view) = 0;

  virtual void SetBounds(const gfx::Rect& bounds) = 0;
  virtual void SetBackgroundColor(SkColor color) = 0;

 protected:
  NativeView(const mate::Dictionary& options);

 private:
  DISALLOW_COPY_AND_ASSIGN(NativeView);
};

}  // namespace atom

#endif  // ATOM_BROWSER_NATIVE_VIEW_H_
