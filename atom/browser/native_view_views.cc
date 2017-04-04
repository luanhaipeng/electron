// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/atom_api_browser_view.h"

#include "ui/gfx/geometry/rect.h"
#include "ui/views/background.h"

namespace atom {

NativeViewViews::NativeViewViews(const mate::Dictionary& options)
    : NativeView(options) {
  // This might be initialized by a subclass.
  if (!view_) {
    view_ = new views::View();
  }
}

NativeViewViews::~NativeViewViews() {
  view_ = nullptr;
}

gfx::NativeView NativeViewViews::GetView() {
  return view_;
}

void NativeViewViews::AddChildView(NativeView* nativeView) {
  if (!nativeView) {
    return;
  }

  auto* child_view = nativeView->GetView();
  view_->AddChildView(child_view);
}

void NativeViewViews::RemoveChildView(NativeView* nativeView) {
  if (!nativeView) {
    return;
  }

  auto* child_view = nativeView->GetView();
  view_->RemoveChildView(child_view);
}

void NativeViewViews::SetBounds(const gfx::Rect& bounds) {
  view_->SetBoundsRect(bounds);
}

void NativeViewViews::SetBackgroundColor(SkColor color) {
  view_->set_background(views::Background::CreateSolidBackground(color));
}

// static
NativeView* NativeView::Create(const mate::Dictionary& options) {
  return new NativeViewViews(options);
}

}  // namespace atom
