import { Listener } from '../types/Listener'

export interface Surface {
  readonly width: number
  readonly height: number
}

export interface SurfaceProvider {
  /**
   * @private
   */
  getSurface(): Surface | undefined

  /**
   * Called nce the surface is available to draw (android: onSurfaceTextureAvailable, ios:
   * called almost immediately after the view is created).
   * @private
   */
  addOnSurfaceCreatedListener(listener: (surface: Surface) => void): Listener

  /**
   * @private
   */
  addOnSurfaceDestroyedListener(listener: () => void): Listener
}

export interface FilamentView {
  /**
   * @private
   */
  getSurfaceProvider(): SurfaceProvider
}
