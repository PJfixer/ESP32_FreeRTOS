


#include "bt_spp.h"

static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;


static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_AUTHENTICATE;
static const esp_spp_role_t role_master = ESP_SPP_ROLE_MASTER;

static esp_bd_addr_t peer_bd_addr;
static uint8_t peer_bdname_len;
static char peer_bdname[ESP_BT_GAP_MAX_BDNAME_LEN + 1];
static const char remote_device_name[] = "LGB";
static const esp_bt_inq_mode_t inq_mode = ESP_BT_INQ_MODE_GENERAL_INQUIRY;
static const uint8_t inq_len = 30;
static const uint8_t inq_num_rsps = 0;

#if (SPP_SHOW_MODE == SPP_SHOW_DATA)
#define SPP_DATA_LEN 20
#else
#define SPP_DATA_LEN ESP_SPP_MAX_MTU
#endif
static uint8_t spp_data[SPP_DATA_LEN];


static bool get_name_from_eir(uint8_t *eir, char *bdname, uint8_t *bdname_len)
{
    uint8_t *rmt_bdname = NULL;
    uint8_t rmt_bdname_len = 0;

    if (!eir) {
        return false;
    }

  //  rmt_bdname = esp_bt_gap_resolve_eir_data(eir, 1, &rmt_bdname_len);
   // rmt_bdname = esp_bt_gap_resolve_eir_data(eir, 2, &rmt_bdname_len);
   // rmt_bdname = esp_bt_gap_resolve_eir_data(eir, 3, &rmt_bdname_len); 
	//rmt_bdname = esp_bt_gap_resolve_eir_data(eir, 4, &rmt_bdname_len);
	//rmt_bdname = esp_bt_gap_resolve_eir_data(eir, 5, &rmt_bdname_len);
	//rmt_bdname = esp_bt_gap_resolve_eir_data(eir, 6, &rmt_bdname_len);
	//rmt_bdname = esp_bt_gap_resolve_eir_data(eir, 7, &rmt_bdname_len);
    //rmt_bdname = esp_bt_gap_resolve_eir_data(eir, 8, &rmt_bdname_len);
    rmt_bdname = esp_bt_gap_resolve_eir_data(eir, 9, &rmt_bdname_len); 
   // if (!rmt_bdname) {
     //   rmt_bdname = esp_bt_gap_resolve_eir_data(eir, ESP_BT_EIR_TYPE_SHORT_LOCAL_NAME, &rmt_bdname_len);
       // printf("we are here !!! \n");
   // }

    if (rmt_bdname) {
        if (rmt_bdname_len > ESP_BT_GAP_MAX_BDNAME_LEN) {
            rmt_bdname_len = ESP_BT_GAP_MAX_BDNAME_LEN;
           
        }

        if (bdname) {
			
            memcpy(bdname, rmt_bdname, rmt_bdname_len);
            bdname[rmt_bdname_len] = '\0';
        }
        if (bdname_len) {
            *bdname_len = rmt_bdname_len;
        }
        return true;
    }

    return false;
}

static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    switch (event) {
    case ESP_SPP_INIT_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_INIT_EVT");
        esp_bt_dev_set_device_name("ESP32");
        esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
        esp_bt_gap_start_discovery(inq_mode, inq_len, inq_num_rsps);

        break;
    case ESP_SPP_DISCOVERY_COMP_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_DISCOVERY_COMP_EVT status=%d scn_num=%d",param->disc_comp.status, param->disc_comp.scn_num);
        if (param->disc_comp.status == ESP_SPP_SUCCESS) {
            esp_spp_connect(sec_mask, role_master, param->disc_comp.scn[0], peer_bd_addr);
        }
        break;
    case ESP_SPP_OPEN_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_OPEN_EVT");
        esp_spp_write(param->srv_open.handle, SPP_DATA_LEN, spp_data);
        break;
    case ESP_SPP_CLOSE_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CLOSE_EVT");
        break;
    case ESP_SPP_START_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_START_EVT");
        break;
    case ESP_SPP_CL_INIT_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CL_INIT_EVT");
        break;
    case ESP_SPP_DATA_IND_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_DATA_IND_EVT");
        break;
    case ESP_SPP_CONG_EVT:
#if (SPP_SHOW_MODE == SPP_SHOW_DATA)
        ESP_LOGI(SPP_TAG, "ESP_SPP_CONG_EVT cong=%d", param->cong.cong);
#endif
        if (param->cong.cong == 0) {
            esp_spp_write(param->cong.handle, SPP_DATA_LEN, spp_data);
        }
        break;
    case ESP_SPP_WRITE_EVT:
#if (SPP_SHOW_MODE == SPP_SHOW_DATA)
        ESP_LOGI(SPP_TAG, "ESP_SPP_WRITE_EVT len=%d cong=%d", param->write.len , param->write.cong);
        esp_log_buffer_hex("",spp_data,SPP_DATA_LEN);
#else
     
#endif
        if (param->write.cong == 0) {
            esp_spp_write(param->write.handle, SPP_DATA_LEN, spp_data);
        }
        break;
    case ESP_SPP_SRV_OPEN_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_SRV_OPEN_EVT");
        break;
    default:
        break;
    }
}

static void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch(event){
    case ESP_BT_GAP_DISC_RES_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_DISC_RES_EVT");
        //esp_log_buffer_hex(SPP_TAG, param->disc_res.bda, ESP_BD_ADDR_LEN);
	
        for (int i = 0; i < param->disc_res.num_prop; i++){
            if (param->disc_res.prop[i].type == ESP_BT_GAP_DEV_PROP_EIR && get_name_from_eir(param->disc_res.prop[i].val, peer_bdname, &peer_bdname_len)){
                esp_log_buffer_char(SPP_TAG, peer_bdname, peer_bdname_len);
                if (strlen(remote_device_name) == peer_bdname_len && strncmp(peer_bdname, remote_device_name, peer_bdname_len) == 0) {  // if length and string content match the one we are looking for
                    memcpy(peer_bd_addr, param->disc_res.bda, ESP_BD_ADDR_LEN);
                    esp_spp_start_discovery(peer_bd_addr);  // start to discover the SPP profile
                    esp_bt_gap_cancel_discovery();  // Generic acces profile is not needed anymore since we find our device , so we stop the GAP discovery
                }
            }
        }
        break;
    case ESP_BT_GAP_DISC_STATE_CHANGED_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_DISC_STATE_CHANGED_EVT");
        break;
    case ESP_BT_GAP_RMT_SRVCS_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_RMT_SRVCS_EVT");
        break;
    case ESP_BT_GAP_RMT_SRVC_REC_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_RMT_SRVC_REC_EVT");
        break;
    case ESP_BT_GAP_AUTH_CMPL_EVT:{
        if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(SPP_TAG, "authentication success: %s", param->auth_cmpl.device_name);
            esp_log_buffer_hex(SPP_TAG, param->auth_cmpl.bda, ESP_BD_ADDR_LEN);
        } else {
            ESP_LOGE(SPP_TAG, "authentication failed, status:%d", param->auth_cmpl.stat);
        }
        break;
    }
    case ESP_BT_GAP_PIN_REQ_EVT:{
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_PIN_REQ_EVT min_16_digit:%d", param->pin_req.min_16_digit);
        if (param->pin_req.min_16_digit) {
            ESP_LOGI(SPP_TAG, "Input pin code: 0000 0000 0000 0000");
            esp_bt_pin_code_t pin_code = {0};
            esp_bt_gap_pin_reply(param->pin_req.bda, true, 16, pin_code);
        } else {
            ESP_LOGI(SPP_TAG, "Input pin code: 1234");
            esp_bt_pin_code_t pin_code;
            pin_code[0] = '1';
            pin_code[1] = '2';
            pin_code[2] = '3';
            pin_code[3] = '4';
            esp_bt_gap_pin_reply(param->pin_req.bda, true, 4, pin_code);
        }
        break;
    }

#if (CONFIG_BT_SSP_ENABLED == true)
    case ESP_BT_GAP_CFM_REQ_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %d", param->cfm_req.num_val);
        esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
        break;
    case ESP_BT_GAP_KEY_NOTIF_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_KEY_NOTIF_EVT passkey:%d", param->key_notif.passkey);
        break;
    case ESP_BT_GAP_KEY_REQ_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
        break;
#endif

    default:
        break;
    }
}











void init_bt(void) {
	

    for (int i = 0; i < SPP_DATA_LEN; ++i) {
        spp_data[i] = i;
    }

   esp_err_t ret;

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_init()) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize bluedroid failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_enable()) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable bluedroid failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_gap_register_callback(esp_bt_gap_cb)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s gap register failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_spp_register_callback(esp_spp_cb)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp register failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_spp_init(esp_spp_mode)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp init failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

#if (CONFIG_BT_SSP_ENABLED == true)
    /* Set default parameters for Secure Simple Pairing */
    esp_bt_sp_param_t param_type = ESP_BT_SP_IOCAP_MODE;
    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_IO;
    esp_bt_gap_set_security_param(param_type, &iocap, sizeof(uint8_t));
#endif

    /*
     * Set default parameters for Legacy Pairing
     * Use variable pin, input pin code when pairing
     */
    esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_VARIABLE;
    esp_bt_pin_code_t pin_code;
    esp_bt_gap_set_pin(pin_type, 0, pin_code);
    
 
}

