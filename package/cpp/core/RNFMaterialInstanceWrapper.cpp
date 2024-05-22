//
// Created by Hanno Gödecke on 20.03.24.
//

#include "RNFMaterialInstanceWrapper.h"
#include "RNFCullingModeEnum.h"
#include "RNFTransparencyModeEnum.h"
#include <filament/Material.h>

namespace margelo {
void MaterialInstanceWrapper::loadHybridMethods() {
  registerHybridMethod("setCullingMode", &MaterialInstanceWrapper::setCullingMode, this);
  registerHybridMethod("setTransparencyMode", &MaterialInstanceWrapper::setTransparencyMode, this);
  registerHybridMethod("changeAlpha", &MaterialInstanceWrapper::changeAlpha, this);
  registerHybridMethod("setParameter", &MaterialInstanceWrapper::setParameter, this);
  registerHybridMethod("setBaseColorSRGB", &MaterialInstanceWrapper::setBaseColorSRGB, this);
  registerHybridGetter("getName", &MaterialInstanceWrapper::getName, this);
}

void MaterialInstanceWrapper::setCullingMode(std::string mode) {
  std::unique_lock lock(_mutex);

  backend::CullingMode cullingMode;
  EnumMapper::convertJSUnionToEnum(mode, &cullingMode);
  _materialInstance->setCullingMode(cullingMode);
}

void MaterialInstanceWrapper::setTransparencyMode(std::string mode) {
  std::unique_lock lock(_mutex);

  TransparencyMode transparencyMode;
  EnumMapper::convertJSUnionToEnum(mode, &transparencyMode);
  _materialInstance->setTransparencyMode(transparencyMode);
}

void MaterialInstanceWrapper::changeAlpha(MaterialInstance* materialInstance, double alpha) {
  // Clip alpha to 0-1
  alpha = std::clamp(alpha, 0.0, 1.0);

  // Customer's default:
  materialInstance->setTransparencyMode(TransparencyMode::TWO_PASSES_ONE_SIDE);

  math::float4 rgba = materialInstance->getParameter<math::float4>("baseColorFactor");
  materialInstance->setParameter("baseColorFactor", math::float4({rgba.r, rgba.g, rgba.b, alpha}));
}

void MaterialInstanceWrapper::changeAlpha(double alpha) {
  std::unique_lock lock(_mutex);

  changeAlpha(_materialInstance, alpha);
}

void MaterialInstanceWrapper::setParameter(std::string name, double value) {
  std::unique_lock lock(_mutex);

  const Material* material = _materialInstance->getMaterial();

  if (!material->hasParameter(name.c_str())) {
    throw std::runtime_error("MaterialInstanceWrapper::setParameter: Material does not have parameter \"" + name + "\"!");
  }

  _materialInstance->setParameter(name.c_str(), (float)value);
}

void MaterialInstanceWrapper::setBaseColorSRGB(std::vector<double> rgba) {
  std::unique_lock lock(_mutex);

  if (rgba.size() != 4) {
    throw std::runtime_error("MaterialInstanceWrapper::setBaseColorSRGB: RGBA vector must have 4 elements!");
  }

  double r = rgba[0];
  double g = rgba[1];
  double b = rgba[2];
  double a = rgba[3];

  _materialInstance->setParameter("baseColorFactor", math::float4({r, g, b, a}));
}

std::string MaterialInstanceWrapper::getName() {
  std::unique_lock lock(_mutex);

  return _materialInstance->getName();
}

} // namespace margelo