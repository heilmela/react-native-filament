//
//  AppleFilamentProxy.h
//  react-native-filament
//
//  Created by Marc Rousavy on 20.02.24.
//  Copyright © 2023 mrousavy. All rights reserved.
//

#pragma once

#include "Dispatcher.h"
#include "FilamentBuffer.h"
#include "FilamentProxy.h"
#include "FilamentView.h"
#include <ReactCommon/CallInvoker.h>
#include <jsi/jsi.h>

namespace margelo {

class AppleFilamentProxy : public FilamentProxy {
public:
  explicit AppleFilamentProxy(jsi::Runtime* runtime, std::shared_ptr<react::CallInvoker> callInvoker);
  ~AppleFilamentProxy();

public:
  std::shared_ptr<FilamentBuffer> loadAsset(std::string path) override;
  std::shared_ptr<FilamentView> findFilamentView(int modelId) override;
  std::shared_ptr<Choreographer> createChoreographer() override;
  std::shared_ptr<Dispatcher> getUIDispatcher() override;
  std::shared_ptr<Dispatcher> getBackgroundDispatcher() override;

  jsi::Runtime& getRuntime() override;
  std::shared_ptr<react::CallInvoker> getCallInvoker() override;

private:
  jsi::Runtime* _runtime;
  std::shared_ptr<react::CallInvoker> _callInvoker;
  std::shared_ptr<Dispatcher> _uiDispatcher;
  std::shared_ptr<Dispatcher> _backgroundDispatcher;
};

} // namespace margelo
