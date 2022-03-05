/******************************************************************************/
/** 模块名称：不带操作系统LwIP以太网通讯                                     **/
/** 文件名称：tcpprocess.h                                                   **/
/** 版    本：V1.0.0                                                         **/
/** 简    介：用于实现基于LwIP的TCP服务器和客户端功能                        **/
/**--------------------------------------------------------------------------**/
/** 修改记录：                                                               **/
/**     版本      日期              作者              说明                   **/
/**     V1.0.0  2018-08-01          木南              创建文件               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __TCP_PROCESS_H
#define __TCP_PROCESS_H



/* TCP服务器初始化 */
void Tcp_Server_Initialization(void);

/* TCP服务器初始化 */
void Tcp_Client_Initialization(void);

#endif

/*********** (C) COPYRIGHT 1999-2018 Moonan Technology *********END OF FILE****/