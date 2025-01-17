#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// On Windows, handle export vs import
#if defined(_WIN32)
  #ifdef BUILDING_RADAR_BRIDGE
    // Building this library => export symbols
    #define RADAR_BRIDGE_API __declspec(dllexport)
  #else
    // Consuming this library => import symbols
    #define RADAR_BRIDGE_API __declspec(dllimport)
  #endif
#else
  // On Linux/macOS => default visibility
  #define RADAR_BRIDGE_API __attribute__((visibility("default")))
#endif

// Forward declarations instead of including <wx/glcanvas.h> or <wx/geometry.h>
typedef class wxGLContext wxGLContext;   // treat them as incomplete types
typedef class wxSize wxSize;

// Forward declare the interfaces
struct IRadarAPI;
struct IRadarOverlay;

/**
 * Global pointer that radar_pi sets at runtime. If null, means radar_pi isn't loaded.
 */
extern RADAR_BRIDGE_API IRadarAPI* g_radarAPI;

/**
 * Interface for a plugin wanting to draw on the radar's OpenGL canvas.
 * The radar plugin calls OnRadarOverlayRender(...) during its GL draw cycle.
 *
 * We only pass pointers to wxGLContext and wxSize. We do NOT call their methods,
 * so we don't need the actual wxWidgets definitions here.
 */
struct IRadarOverlay {
    virtual ~IRadarOverlay() {}

    virtual void OnRadarOverlayRender(wxGLContext* pcontext,
                                      const wxSize* canvasSize,
                                      float radarRangePx) = 0;
};

/**
 * The main radar API that radar_pi implements.
 * 
 * Example methods for setting radar range/gain, plus registering overlays.
 */
struct IRadarAPI {
    virtual ~IRadarAPI() {}

    // Example: sets the radar range in NM
    virtual void SetRadarRangeNM(double range_nm) = 0;
    virtual double GetRadarRangeNM() const = 0;

    // Example: sets the radar gain (0..100)
    virtual void SetGain(int gain) = 0;
    virtual int GetGain() const = 0;

    // Overlay registration
    virtual void RegisterOverlayRenderer(IRadarOverlay* overlay) = 0;
    virtual void UnregisterOverlayRenderer(IRadarOverlay* overlay) = 0;

    virtual IRadarOverlay* GetOverlay() const = 0;

};

#ifdef __cplusplus
}
#endif
