// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/native_view_mac.h"

#include "skia/ext/skia_utils_mac.h"
#include "ui/gfx/geometry/rect.h"

namespace atom {

NativeViewMac::NativeViewMac(const mate::Dictionary& options)
    : NativeView(options) {
  // This might be initialized by a subclass.
  if (!view_) {
    view_ = [[NSView alloc] init];
  }
}

NativeViewMac::~NativeViewMac() {
  view_ = nullptr;
}

gfx::NativeView NativeViewMac::GetView() {
  return view_;
}

void NativeViewMac::AddChildView(NativeView* nativeView) {
  if (!nativeView) {
    return;
  }

  auto* child_view = nativeView->GetView();
  [view_ addSubview:child_view positioned:NSWindowAbove relativeTo:nil];
  [child_view setHidden:NO];
}

void NativeViewMac::RemoveChildView(NativeView* nativeView) {
  if (!nativeView) {
    return;
  }

  auto* child_view = nativeView->GetView();
  if (child_view.superview == view_) {
    [child_view removeFromSuperview];
  }
}

void NativeViewMac::SetBounds(const gfx::Rect& bounds) {
  auto* superview = view_.superview;
  const auto superview_height = superview ? superview.frame.size.height : 0;
  view_.frame =
      NSMakeRect(bounds.x(), superview_height - bounds.y() - bounds.height(),
                 bounds.width(), bounds.height());
}

void NativeViewMac::SetBackgroundColor(SkColor color) {
  view_.wantsLayer = YES;
  view_.layer.backgroundColor = skia::CGColorCreateFromSkColor(color);
}

// static
NativeView* NativeView::Create(const mate::Dictionary& options) {
  return new NativeViewMac(options);
}

}  // namespace atom
