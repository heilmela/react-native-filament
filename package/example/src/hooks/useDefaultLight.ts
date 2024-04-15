import { Platform } from 'react-native'
import { Engine, useAsset, useEntityInScene, useLightEntity, useLightManager, useScene, useWorkletEffect } from 'react-native-filament'

const indirectLightPath = Platform.select({
  android: 'custom/default_env_ibl.ktx',
  ios: 'default_env_ibl.ktx',
})!

export function useDefaultLight(engine: Engine, enableDirectionalLight = true) {
  const lightBuffer = useAsset({ path: indirectLightPath })
  const scene = useScene(engine)
  const lightManager = useLightManager(engine)

  useWorkletEffect(() => {
    'worklet'

    if (lightBuffer == null) return
    engine.setIndirectLight(lightBuffer, 25_000, undefined)
  }, [engine, lightBuffer, scene])

  const directionalLight = useLightEntity(lightManager, {
    type: 'directional',
    castShadows: true,
    colorKelvin: 6_500,
    direction: [0, -1, 0],
    intensity: enableDirectionalLight ? 10_000 : 0,
    position: [0, 0, 0],
  })
  useEntityInScene(scene, directionalLight)
}
