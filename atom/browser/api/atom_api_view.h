// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_API_ATOM_API_VIEW_H_
#define ATOM_BROWSER_API_ATOM_API_VIEW_H_

#include <memory>
#include <string>

#include "atom/browser/api/trackable_object.h"
#include "native_mate/handle.h"

namespace gfx {
class Rect;
}

namespace mate {
class Arguments;
class Dictionary;
}

namespace atom {

class NativeView;

namespace api {

class View : public mate::TrackableObject<View> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  NativeView* view() const { return view_.get(); }

  int32_t ID() const;

 protected:
  View(v8::Isolate* isolate,
       v8::Local<v8::Object> wrapper,
       const mate::Dictionary& options);
  ~View() override;

 private:
  void Init(v8::Isolate* isolate,
            v8::Local<v8::Object> wrapper,
            const mate::Dictionary& options);

  void AddChildView(v8::Local<v8::Object> value, mate::Arguments* args);
  void RemoveChildView(v8::Local<v8::Object> value, mate::Arguments* args);

  void SetBounds(const gfx::Rect& bounds);
  void SetBackgroundColor(const std::string& color_name);

  std::unique_ptr<NativeView> view_;

  DISALLOW_COPY_AND_ASSIGN(View);
};

}  // namespace api

}  // namespace atom

#endif  // ATOM_BROWSER_API_ATOM_API_VIEW_H_
