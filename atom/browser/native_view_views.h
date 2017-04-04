// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_NATIVE_VIEW_VIEWS_H_
#define ATOM_BROWSER_NATIVE_VIEW_VIEWS_H_

#include "ui/views/view.h"

#include "atom/browser/native_view.h"

namespace atom {

class NativeViewViews : public NativeView {
 public:
  NativeViewViews(const mate::Dictionary& options);
  ~NativeViewViews() override;

  gfx::NativeView GetView() override;

  void AddChildView(NativeView* nativeView) override;
  void RemoveChildView(NativeView* nativeView) override;

  void SetBounds(const gfx::Rect& bounds) override;
  void SetBackgroundColor(SkColor color) override;

 protected:
  views::View* view_ = nullptr;

 private:
  DISALLOW_COPY_AND_ASSIGN(NativeViewViews);
};

}  // namespace atom

#endif  // ATOM_BROWSER_NATIVE_VIEW_VIEWS_H_
