// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/api/atom_api_view.h"

#include "atom/browser/browser.h"
#include "atom/browser/native_view.h"
#include "atom/common/color_util.h"
#include "atom/common/native_mate_converters/gfx_converter.h"
#include "atom/common/native_mate_converters/value_converter.h"
#include "atom/common/options_switches.h"
#include "native_mate/constructor.h"
#include "native_mate/dictionary.h"

#include "ui/gfx/geometry/rect.h"

#include "atom/common/node_includes.h"

namespace atom {

namespace api {

View::View(v8::Isolate* isolate,
           v8::Local<v8::Object> wrapper,
           const mate::Dictionary& options) {
  Init(isolate, wrapper, options);
}

void View::Init(v8::Isolate* isolate,
                v8::Local<v8::Object> wrapper,
                const mate::Dictionary& options) {
  view_.reset(NativeView::Create(options));

  InitWith(isolate, wrapper);
}

View::~View() {}

// static
mate::WrappableBase* View::New(mate::Arguments* args) {
  if (!Browser::Get()->is_ready()) {
    args->ThrowError("Cannot create View before app is ready");
    return nullptr;
  }

  if (args->Length() > 1) {
    args->ThrowError();
    return nullptr;
  }

  mate::Dictionary options;
  if (!(args->Length() == 1 && args->GetNext(&options))) {
    options = mate::Dictionary::CreateEmpty(args->isolate());
  }

  return new View(args->isolate(), args->GetThis(), options);
}

int32_t View::ID() const {
  return weak_map_id();
}

void View::AddChildView(v8::Local<v8::Object> value, mate::Arguments* args) {
  mate::Handle<class View> child_view;
  if (value->IsNull() || !mate::ConvertFromV8(isolate(), value, &child_view) ||
      child_view.get() == this) {
    args->ThrowError("Invalid argument");
    return;
  }

  view_->AddChildView(child_view->view());
}

void View::RemoveChildView(v8::Local<v8::Object> value, mate::Arguments* args) {
  mate::Handle<class View> child_view;
  if (value->IsNull() || !mate::ConvertFromV8(isolate(), value, &child_view) ||
      child_view.get() == this) {
    args->ThrowError("Invalid argument");
    return;
  }

  view_->RemoveChildView(child_view->view());
}

void View::SetBounds(const gfx::Rect& bounds) {
  view_->SetBounds(bounds);
}

void View::SetBackgroundColor(const std::string& color_name) {
  view_->SetBackgroundColor(ParseHexColor(color_name));
}

// static
void View::BuildPrototype(v8::Isolate* isolate,
                          v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "View"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("addChildView", &View::AddChildView)
      .SetMethod("removeChildView", &View::RemoveChildView)
      .SetMethod("setBounds", &View::SetBounds)
      .SetMethod("setBackgroundColor", &View::SetBackgroundColor)
      .SetProperty("id", &View::ID);
}

}  // namespace api

}  // namespace atom

namespace {

using atom::api::View;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* isolate = context->GetIsolate();
  View::SetConstructor(isolate, base::Bind(&View::New));

  mate::Dictionary view(isolate, View::GetConstructor(isolate)->GetFunction());

  mate::Dictionary dict(isolate, exports);
  dict.Set("View", view);
}

}  // namespace

NODE_MODULE_CONTEXT_AWARE_BUILTIN(atom_browser_view, Initialize)
