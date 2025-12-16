# Kernel log explanation for MDIO fallback and -19 errors

This note explains the boot log shown in the request, focusing on why MDIO callbacks defaulted and why device 1 returned `-19` (`SW_NOT_SUPPORTED`).

## Log sections and meaning
- `fal_init: start dev:0 reg_mode:2 ...` – device 0 starts with header/local bus mode; it has no MDIO callbacks, so MDIO is irrelevant to this path.
- `sd_init: mdio_set/mdio_get is NULL ...` – confirms the platform did not supply MDIO callbacks. Because `UK_IF` is compiled (`UK_IF compile state:enabled`), MDIO access for device 0 could fall back to the user-kernel interface if needed.
- `switch node is qca83xx!` – DTS compatibility string identifies the switch as the qca83xx family.
- `mdio bus is present ... mdio_set/mdio_get defaulted ...` – during platform init for device 1 (reg_mode=MDIO), the code finds a registered `mii_bus` and auto-fills the missing callbacks with MDIO bus helpers. This should provide working MDIO access without UK_IF.
- `fal_init: start dev:1 ...` – begins initializing device 1 (chip_type=6, ISISC) using MDIO register mode.
- `hsl_dev_init: 初始化失败 ... rv:-19` – chip init returns `-19` (`SW_NOT_SUPPORTED`). Given MDIO callbacks were populated, this implies the ISISC init path hit an unsupported operation (often an MDIO access still deemed unsupported or another feature gate inside the chip-specific init). The error propagates through `fal_init` and `ssdk_init`, causing `ssdk fal init failed: -19`.
- `qca_mac_disable: API not support` – later error indicating MAC-related API hooks were not provided for the detected hardware, consistent with unsupported operations along the ISISC path.

## Takeaways
- MDIO callbacks were automatically provided from the detected `mii_bus`, so the `-19` is not from missing callbacks alone. The failure likely arises from an unsupported chip feature or a remaining MDIO access that still reports unsupported for this hardware configuration.
