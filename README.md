# MQGammaLess

A MacroQuest plugin that prevents EverQuest from modifying your system's gamma ramp settings. This works around a bug in windowed mode where EverQuest's gamma changes affect your entire desktop instead of just the game window.

## Getting Started

Load the plugin to enable:

```txt
/plugin MQGammaLess
```

When loaded successfully, you'll see the message: `[MQGammaLess] Gamma protection enabled`

## Compatibility

This plugin is only functional on the **ROF2** client. On other client versions, the plugin will load but will not apply any hooks.

## How It Works

The plugin intercepts calls to the Windows GDI function `SetDeviceGammaRamp` and prevents EverQuest from changing your display's gamma settings. This is a harmless no-op that returns success without actually modifying your display.

## Authors

* **Knightly**
