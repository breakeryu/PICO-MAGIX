#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "system_msg_deal.h"
#include "prompt_player.h"
#include "voice_module_uart_protocol.h"
#include "i2c_protocol_module.h"
#include "ci_nvdata_manage.h"
#include "ci_log.h"
#include "ci112x_gpio.h"
#include "ci112x_pwm.h"
///tag-insert-code-pos-1

/**
 * @brief 用户初始化
 *
 */
void userapp_initial(void)
{
    #if CPU_RATE_PRINT
    init_timer3_getresource();
    #endif

    #if MSG_COM_USE_UART_EN
    #if (UART_PROTOCOL_VER == 1)
    uart_communicate_init();
    #elif (UART_PROTOCOL_VER == 2)
    vmup_communicate_init();
    #elif (UART_PROTOCOL_VER == 255)
    UARTInterruptConfig((UART_TypeDef *)UART_PROTOCOL_NUMBER, UART_PROTOCOL_BAUDRATE);
    #endif
    #endif

    #if MSG_USE_I2C_EN
    i2c_communicate_init();
    #endif

#if IIS1_ENABLE == 0
    //IIS1引脚配置为gpio
    Scu_SetDeviceGate(HAL_GPIO2_BASE,ENABLE);
    Scu_SetIOReuse(I2S1_LRCLK_PAD, FIRST_FUNCTION);
    Scu_SetIOReuse(I2S1_SDO_PAD, FIRST_FUNCTION);
    Scu_SetIOReuse(I2S1_SCLK_PAD, FIRST_FUNCTION);
#endif

    ///tag-gpio-init
    pwm_init_t init;

    Scu_SetDeviceGate((unsigned int)GPIO1,ENABLE);
    Scu_SetIOReuse(PWM3_PAD,FIRST_FUNCTION);
    Scu_SetIOPull(PWM3_PAD,DISABLE);
    gpio_set_output_mode(GPIO1,gpio_pin_4);


    Scu_SetDeviceGate((unsigned int)GPIO1,ENABLE);
    Scu_SetIOReuse(PWM4_PAD,FIRST_FUNCTION);
    Scu_SetIOPull(PWM4_PAD,DISABLE);
    gpio_set_output_mode(GPIO1,gpio_pin_5);

    Scu_SetDeviceGate((unsigned int)GPIO1,ENABLE);
    Scu_SetIOReuse(PWM5_PAD,FIRST_FUNCTION);
    Scu_SetIOPull(PWM5_PAD,DISABLE);
    gpio_set_output_mode(GPIO1,gpio_pin_6);


}

/**
 * @brief 处理按键消息（目前未实现该demo）
 *
 * @param key_msg 按键消息
 */
void userapp_deal_key_msg(sys_msg_key_data_t  *key_msg)
{
    (void)(key_msg);
}



/**
 * @brief 按语义ID响应asr消息处理
 *
 * @param asr_msg
 * @param cmd_handle
 * @param semantic_id
 * @return uint32_t
 */
uint32_t deal_asr_msg_by_semantic_id(sys_msg_asr_data_t *asr_msg, cmd_handle_t cmd_handle, uint32_t semantic_id)
{
    uint32_t ret = 1;
    if (PRODUCT_GENERAL == get_product_id_from_semantic_id(semantic_id))
    {
        uint8_t vol;
        int select_index = -1;
        switch(get_function_id_from_semantic_id(semantic_id))
        {
        case VOLUME_UP:        //增大音量
            vol = vol_set(vol_get() + 1);
            select_index = (vol == VOLUME_MAX) ? 1:0;
            break;
        case VOLUME_DOWN:      //减小音量
            vol = vol_set(vol_get() - 1);
            select_index = (vol == VOLUME_MIN) ? 1:0;
            break;
        case MAXIMUM_VOLUME:   //最大音量
            vol_set(VOLUME_MAX);
            break;
        case MEDIUM_VOLUME:  //中等音量
            vol_set(VOLUME_MID);
            break;
        case MINIMUM_VOLUME:   //最小音量
            vol_set(VOLUME_MIN);
            break;
        case TURN_ON_VOICE_BROADCAST:    //开启语音播报
            prompt_player_enable(ENABLE);
            break;
        case TURN_OFF_VOICE_BROADCAST:    //关闭语音播报
            prompt_player_enable(DISABLE);
            break;
        default:
            ret = 0;
            break;
        }
        if (ret)
        {
            #if PLAY_OTHER_CMD_EN
            pause_voice_in();
            prompt_play_by_cmd_handle(cmd_handle, select_index, default_play_done_callback,true);
            #endif
        }
    }
    else
    {
        ret = 0;
    }
    return ret;
}


/**
 * @brief 按命令词id响应asr消息处理
 *
 * @param asr_msg
 * @param cmd_handle
 * @param cmd_id
 * @return uint32_t
 */
uint32_t deal_asr_msg_by_cmd_id(sys_msg_asr_data_t *asr_msg, cmd_handle_t cmd_handle, uint16_t cmd_id)
{
    uint32_t ret = 1;
    int select_index = -1;
    switch(cmd_id)
    {
        ///tag-asr-msg-deal-by-cmd-id-start
        case 2://“打开空调”
        {
        	openLed();
            break;
        }
        case 3://“关闭空调”
        {
        	closeLed();
            break;
        }
        case 4://“除湿模式”
        {
        	blueLedMode();
            break;
        }
        case 5://"关闭除湿"
        {
        	redLedMode();
            break;
        }
        case 6://"关闭睡眠模式"
        {
        	greenLedMode();
            break;
        }
        ///tag-asr-msg-deal-by-cmd-id-end
        default:
            ret = 0;
            break;
    }

    if (ret && select_index >= -1)
    {
        #if PLAY_OTHER_CMD_EN
        pause_voice_in();
        prompt_play_by_cmd_handle(cmd_handle, select_index, default_play_done_callback,true);
        #endif
    }

    return ret;
}

/**
 * @brief 用户自定义消息处理
 *
 * @param msg
 * @return uint32_t
 */
uint32_t deal_userdef_msg(sys_msg_t *msg)
{
    uint32_t ret = 1;
    switch(msg->msg_type)
    {
    /* 按键消息 */
    case SYS_MSG_TYPE_KEY:
    {
        sys_msg_key_data_t *key_rev_data;
        key_rev_data = &msg->msg_data.key_data;
        userapp_deal_key_msg(key_rev_data);
        break;
    }
    #if MSG_COM_USE_UART_EN
    /* CI串口协议消息 */
    case SYS_MSG_TYPE_COM:
    {
		#if ((UART_PROTOCOL_VER == 1) || (UART_PROTOCOL_VER == 2))
    	sys_msg_com_data_t *com_rev_data;
        com_rev_data = &msg->msg_data.com_data;
        userapp_deal_com_msg(com_rev_data);
        #endif
        break;
    }
    #endif
    /* CI IIC 协议消息 */
    #if MSG_USE_I2C_EN
    case SYS_MSG_TYPE_I2C:
    {
        sys_msg_i2c_data_t *i2c_rev_data;
        i2c_rev_data = &msg->msg_data.i2c_data;
        userapp_deal_i2c_msg(i2c_rev_data);
        break;
    }
    #endif
    default:
        break;
    }
    return ret;
}


void openLed(void){
	gpio_set_output_level_single(GPIO1,gpio_pin_4,0);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_5,0);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_6,0);   //输出低电平
}

void closeLed(void){

	gpio_set_output_level_single(GPIO1,gpio_pin_4,1);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_5,1);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_6,1);   //输出低电平

}


void blueLedMode(void){
	gpio_set_output_level_single(GPIO1,gpio_pin_4,1);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_5,1);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_6,0);   //输出低电平
}


void greenLedMode(void){
	gpio_set_output_level_single(GPIO1,gpio_pin_4,0);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_5,1);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_6,1);   //输出低电平
}

void redLedMode(void){
	gpio_set_output_level_single(GPIO1,gpio_pin_4,1);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_5,0);   //输出低电平
	gpio_set_output_level_single(GPIO1,gpio_pin_6,1);   //输出低电平
}

