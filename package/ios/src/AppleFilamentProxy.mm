//
//  AppleFilamentProxy.mm
//  react-native-filament
//
//  Created by Marc Rousavy on 20.02.24.
//

#import "AppleFilamentProxy.h"
#import "AppleChoreographer.h"
#import "AppleFilamentView.h"
#import "FilamentMetalView.h"
#import "FilamentView.h"
#import <Foundation/Foundation.h>
#import <React/RCTBridge+Private.h>
#import <React/RCTBridge.h>
#import <React/RCTUIManager.h>
#import <React/RCTUtils.h>

namespace margelo {

AppleFilamentProxy::AppleFilamentProxy(jsi::Runtime* runtime, std::shared_ptr<react::CallInvoker> callInvoker)
    : _runtime(runtime), _callInvoker(callInvoker) {}

AppleFilamentProxy::~AppleFilamentProxy() {
  // TODO(hanno): cleanup here?
}

jsi::Runtime& AppleFilamentProxy::getRuntime() {
  if (_runtime == nullptr) {
    [[unlikely]];
    throw std::runtime_error("JSI Runtime was null!");
  }
  return *_runtime;
}

std::shared_ptr<react::CallInvoker> AppleFilamentProxy::getCallInvoker() {
  return _callInvoker;
}

int AppleFilamentProxy::loadModel(std::string path) {
  // TODO(hanno): Implement model loading here
  return 13;
}

std::shared_ptr<FilamentView> AppleFilamentProxy::findFilamentView(int viewId) {
  // TODO(marc): Make this async when JSIConvert can do that
  std::shared_ptr<AppleFilamentView> result;
  RCTUnsafeExecuteOnMainQueueSync([viewId, &result]() {
    RCTBridge* currentBridge = [RCTBridge currentBridge]; // <-- from <React/RCTBridge+Private.h>
    RCTUIManager* uiManager = currentBridge.uiManager;    // <-- from <React/RCTUIManager.h>
    UIView* anonymousView = [uiManager viewForReactTag:[NSNumber numberWithInt:viewId]];
    FilamentMetalView* view = (FilamentMetalView*)anonymousView;
    result.reset(new AppleFilamentView(view));
  });
  return std::static_pointer_cast<FilamentView>(result);
}

std::shared_ptr<Choreographer> AppleFilamentProxy::createChoreographer() {
  std::shared_ptr<AppleChoreographer> choreographer = std::make_shared<AppleChoreographer>();
  return std::static_pointer_cast<Choreographer>(choreographer);
}

} // namespace margelo
