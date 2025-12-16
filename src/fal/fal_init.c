/*
 * Copyright (c) 2012, 2016-2018, The Linux Foundation. All rights reserved.
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*qca808x_start*/
/**
 * @defgroup fal_init FAL_INIT
 * @{
 */
#include "sw.h"
#include "hsl.h"
#include "hsl_dev.h"
#include "hsl_api.h"
/*qca808x_end*/
#include "fal_vlan.h"
#include "adpt.h"
/*qca808x_start*/
/**
 * @brief Init fal layer.
 * @details Comments:
 *   This operation will init fal layer and hsl layer
 * @param[in] dev_id device id
 * @param[in] cfg configuration for initialization
 * @return SW_OK or error code
 */
sw_error_t
fal_init(a_uint32_t dev_id, ssdk_init_cfg *cfg)
{
    sw_error_t rv;
    HSL_DEV_ID_CHECK(dev_id);

    if (!cfg) {
        SSDK_ERROR("fal_init: cfg is NULL for dev:%u\n", dev_id);
        return SW_BAD_PTR;
    }

    SSDK_ERROR("fal_init: start dev:%u reg_mode:%d cpu_mode:%d chip_type:%d chip_revision:%u nl_prot:%u chip_spec_cfg:%p port_cfg_cpu_bmp:0x%x port_cfg_lan_bmp:0x%x port_cfg_wan_bmp:0x%x port_cfg_inner_bmp:0x%x mac_mode:%u mac_mode1:%u mac_mode2:%u phy_id:%u\n",
        dev_id, cfg->reg_mode, cfg->cpu_mode, cfg->chip_type, cfg->chip_revision,
        cfg->nl_prot, cfg->chip_spec_cfg, cfg->port_cfg.cpu_bmp, cfg->port_cfg.lan_bmp,
        cfg->port_cfg.wan_bmp, cfg->port_cfg.inner_bmp, cfg->mac_mode, cfg->mac_mode1,
        cfg->mac_mode2, cfg->phy_id);

    rv = hsl_api_init(dev_id);
    if (rv != SW_OK) {
        SSDK_ERROR("fal_init: hsl_api_init failed dev:%u rv:%d cfg_reg_mode:%d cfg_cpu_mode:%d cfg_chip_type:%d cfg_chip_revision:%u cfg_nl_prot:%u cfg_chip_spec_cfg:%p cfg_port_cfg_cpu_bmp:0x%x cfg_port_cfg_lan_bmp:0x%x cfg_port_cfg_wan_bmp:0x%x cfg_port_cfg_inner_bmp:0x%x cfg_mac_mode:%u cfg_mac_mode1:%u cfg_mac_mode2:%u cfg_phy_id:%u\n",
            dev_id, rv, cfg->reg_mode, cfg->cpu_mode, cfg->chip_type,
            cfg->chip_revision, cfg->nl_prot, cfg->chip_spec_cfg,
            cfg->port_cfg.cpu_bmp, cfg->port_cfg.lan_bmp, cfg->port_cfg.wan_bmp,
            cfg->port_cfg.inner_bmp, cfg->mac_mode, cfg->mac_mode1, cfg->mac_mode2,
            cfg->phy_id);
        return rv;
    }

    rv = hsl_dev_init(dev_id, cfg);
    if (rv != SW_OK) {
        SSDK_ERROR("fal_init: hsl_dev_init failed dev:%u rv:%d cfg_reg_mode:%d cfg_cpu_mode:%d cfg_chip_type:%d cfg_chip_revision:%u cfg_nl_prot:%u cfg_chip_spec_cfg:%p cfg_port_cfg_cpu_bmp:0x%x cfg_port_cfg_lan_bmp:0x%x cfg_port_cfg_wan_bmp:0x%x cfg_port_cfg_inner_bmp:0x%x cfg_mac_mode:%u cfg_mac_mode1:%u cfg_mac_mode2:%u cfg_phy_id:%u\n",
            dev_id, rv, cfg->reg_mode, cfg->cpu_mode, cfg->chip_type,
            cfg->chip_revision, cfg->nl_prot, cfg->chip_spec_cfg,
            cfg->port_cfg.cpu_bmp, cfg->port_cfg.lan_bmp, cfg->port_cfg.wan_bmp,
            cfg->port_cfg.inner_bmp, cfg->mac_mode, cfg->mac_mode1, cfg->mac_mode2,
            cfg->phy_id);
        return rv;
    }
/*qca808x_end*/
#ifdef IN_VLAN
    rv = fal_vlan_init(dev_id);
    if (rv != SW_OK) {
        SSDK_ERROR("fal_init: fal_vlan_init failed dev:%u rv:%d cfg_reg_mode:%d cfg_cpu_mode:%d cfg_chip_type:%d cfg_chip_revision:%u cfg_nl_prot:%u cfg_chip_spec_cfg:%p cfg_port_cfg_cpu_bmp:0x%x cfg_port_cfg_lan_bmp:0x%x cfg_port_cfg_wan_bmp:0x%x cfg_port_cfg_inner_bmp:0x%x cfg_mac_mode:%u cfg_mac_mode1:%u cfg_mac_mode2:%u cfg_phy_id:%u\n",
            dev_id, rv, cfg->reg_mode, cfg->cpu_mode, cfg->chip_type,
            cfg->chip_revision, cfg->nl_prot, cfg->chip_spec_cfg,
            cfg->port_cfg.cpu_bmp, cfg->port_cfg.lan_bmp, cfg->port_cfg.wan_bmp,
            cfg->port_cfg.inner_bmp, cfg->mac_mode, cfg->mac_mode1, cfg->mac_mode2,
            cfg->phy_id);
        return rv;
    }
#endif

    rv = adpt_init(dev_id, cfg);
    if (rv != SW_OK) {
        SSDK_ERROR("fal_init: adpt_init failed dev:%u rv:%d cfg_reg_mode:%d cfg_cpu_mode:%d cfg_chip_type:%d cfg_chip_revision:%u cfg_nl_prot:%u cfg_chip_spec_cfg:%p cfg_port_cfg_cpu_bmp:0x%x cfg_port_cfg_lan_bmp:0x%x cfg_port_cfg_wan_bmp:0x%x cfg_port_cfg_inner_bmp:0x%x cfg_mac_mode:%u cfg_mac_mode1:%u cfg_mac_mode2:%u cfg_phy_id:%u\n",
            dev_id, rv, cfg->reg_mode, cfg->cpu_mode, cfg->chip_type,
            cfg->chip_revision, cfg->nl_prot, cfg->chip_spec_cfg,
            cfg->port_cfg.cpu_bmp, cfg->port_cfg.lan_bmp, cfg->port_cfg.wan_bmp,
            cfg->port_cfg.inner_bmp, cfg->mac_mode, cfg->mac_mode1, cfg->mac_mode2,
            cfg->phy_id);
        return rv;
    }
/*qca808x_start*/

    return rv;
}
/*qca808x_end*/

static sw_error_t
_fal_reset(a_uint32_t dev_id)
{
    sw_error_t rv;
    hsl_api_t *p_api;

    SW_RTN_ON_NULL(p_api = hsl_api_ptr_get(dev_id));

    if (NULL == p_api->dev_reset)
        return SW_NOT_SUPPORTED;

#ifdef IN_VLAN
    rv = fal_vlan_reset(dev_id);
    SW_RTN_ON_ERROR(rv);
#endif

    rv = p_api->dev_reset(dev_id);
    return rv;
}

static sw_error_t
_fal_ssdk_cfg(a_uint32_t dev_id, ssdk_cfg_t *ssdk_cfg)
{
    sw_error_t rv;
    HSL_DEV_ID_CHECK(dev_id);

    rv = hsl_ssdk_cfg(dev_id, ssdk_cfg);

    return rv;
}

static sw_error_t
_fal_ppe_capacity_get(a_uint32_t dev_id, fal_ppe_tbl_caps_t *ppe_capacity)
{
    return adpt_ppe_capacity_get(dev_id, ppe_capacity);
}

/*qca808x_start*/
sw_error_t
fal_cleanup(a_uint32_t dev_id)
{
    sw_error_t rv;

    rv = hsl_dev_cleanup(dev_id);
    SW_RTN_ON_ERROR(rv);
/*qca808x_end*/
#ifdef IN_VLAN
    rv = fal_vlan_cleanup(dev_id);
    SW_RTN_ON_ERROR(rv);
#endif
/*qca808x_start*/
    return SW_OK;
}
/*qca808x_end*/
/**
 * @brief Reset fal layer.
 * @details Comments:
 *   This operation will reset fal layer and hsl layer
 * @param[in] dev_id device id
 * @return SW_OK or error code
 */
sw_error_t
fal_reset(a_uint32_t dev_id)
{
    sw_error_t rv;

    FAL_API_LOCK;
    rv = _fal_reset(dev_id);
    FAL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get SSDK config infomation.
 * @param[in] dev_id device id
 * @param[out] ssdk_cfg SSDK config infomation
 * @return SW_OK or error code
 */
sw_error_t
fal_ssdk_cfg(a_uint32_t dev_id, ssdk_cfg_t *ssdk_cfg)
{
    sw_error_t rv;

    FAL_API_LOCK;
    rv = _fal_ssdk_cfg(dev_id, ssdk_cfg);
    FAL_API_UNLOCK;
    return rv;
}

sw_error_t
fal_switch_devid_get(ssdk_chip_type chip_type, a_uint32_t *pdev_id)
{
	sw_error_t rv = SW_OK;
	ssdk_cfg_t cfg = {0};
	a_uint32_t dev_id = 0;

	for(dev_id = 0; dev_id < SW_MAX_NR_DEV; dev_id++) {
		rv = _fal_ssdk_cfg(dev_id, &cfg);
		if(rv == SW_OK && cfg.init_cfg.chip_type == chip_type) {
			*pdev_id = dev_id;
			return rv;
		}
	}
	return SW_FAIL;
}

sw_error_t
fal_ppe_capacity_get(a_uint32_t dev_id, fal_ppe_tbl_caps_t *ppe_capacity)
{
    sw_error_t rv;

    FAL_API_LOCK;
    rv = _fal_ppe_capacity_get(dev_id, ppe_capacity);
    FAL_API_UNLOCK;
    return rv;
}

EXPORT_SYMBOL(fal_switch_devid_get);
EXPORT_SYMBOL(fal_ppe_capacity_get);

/**
 * @}
 */
