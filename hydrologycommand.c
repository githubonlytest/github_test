
#include "message.h"
#include "hydrologycommand.h"
#include <string.h>
#include "stdint.h"

void RS485_Dir(char inout)
{
	
}

void RS485_SerilWrite(char *buffer,int len)
{
	
}

void RS485_SerilRead(char *buffer,int len)
{
	
}

void RS485_Delay(char timeout)
{
	
}

void RS485_ValueDefine(char *buffer,char *value,int index)
{

}
 
void RS485_Send(char device,char function,char reg_addrH,char reg_addrL,char timeout)
{
	char command[8];
	short crc = 0;
	
	command[0] = device;
	command[1] = function;
	command[2] = reg_addrH >> 8;
	command[3] = reg_addrL % 256;
	command[4] = 0;
	command[5] = 2;
	crc = hydrologyCRC16(command,6);
	command[6] = crc % 256;
	command[7] = crc >> 8;
	RS485_Dir(1);
	RS485_SerilWrite(command,8);
	RS485_Delay(timeout);
}

void RS485_Read(char *buffer)
{
	char temp_buffer[9];
	short crc1 = 0;
	short crc2 = 0;
	
	RS485_SerilRead(temp_buffer,9);
	crc1 = hydrologyCRC16(temp_buffer,7);
	crc2 = temp_buffer[8]<<8 | temp_buffer[7];
	if(crc1 == crc2)
	{
		memcpy(&temp_buffer[3],temp_buffer,4);
	}
//	else
//		printf("RS485 crc check failed!");
}

void Hydrology_ReadRS485(char *value)
{
	char temp_value[5];
	char buffer[4];
	int i = 0;
	long addr = HYDROLOGY_RS4851;
	
	Hydrology_ReadStoreInfo(HYDROLOGY_RS485_COUNT,temp_value,HYDROLOGY_RS485_COUNT_LEN);
	while(temp_value[0])
	{
		Hydrology_ReadStoreInfo(addr,temp_value,HYDROLOGY_RS485_LEN);
		RS485_Send(temp_value[0],temp_value[1],temp_value[2],temp_value[3],temp_value[4]);
		RS485_Read(buffer);
		addr = HYDROLOGY_RS4851 + HYDROLOGY_RS485_LEN;
		RS485_ValueDefine(buffer,value,i++);
	}
}

void hydrologyChangeMode(char M)
{
//    HYDROLOGY_MODE = M;
}


int hydrologyConfigSelect(char* guide,char* value)
{
	int ret;
	
	switch(guide[0])
	{
			case 0x01:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_CENTER_ADDR,value,HYDROLOGY_CENTER_LEN);
					break;
			}
			case 0x02:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_REMOTE_ADDR,value,HYDROLOGY_REMOTE_LEN);
					break;
			}
			case 0x03:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_PASSWORD_ADDR,value,HYDROLOGY_PASSWORD_LEN);
					break;
			}
			case 0x04:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_CENTER1_ADDR,value,HYDROLOGY_CENTER1_ADDR_LEN);
					break;
			}
			case 0x05:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_BACKUP1_ADDR,value,HYDROLOGY_BACKUP1_ADDR_LEN);
					break;
			}
			case 0x06:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_CENTER2_ADDR,value,HYDROLOGY_CENTER2_ADDR_LEN);
					break;
			}
			case 0x07:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_BACKUP2_ADDR,value,HYDROLOGY_BACKUP2_ADDR_LEN);
					break;
			}
			case 0x08:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_CENTER3_ADDR,value,HYDROLOGY_CENTER3_ADDR_LEN);
					break;
			}
			case 0x09:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_BACKUP3_ADDR,value,HYDROLOGY_BACKUP3_ADDR_LEN);
					break;
			}
			case 0x0A:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_CENTER4_ADDR,value,HYDROLOGY_CENTER4_ADDR_LEN);
					break;
			}
			case 0x0B:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_BACKUP4_ADDR,value,HYDROLOGY_BACKUP4_ADDR_LEN);
					break;
			}
			case 0x0C:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WORK_MODE,value,HYDROLOGY_WORK_MODE_LEN);
					break;
			}
			case 0x0D:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ELEMENT_SELECT,value,HYDROLOGY_ELEMENT_SELECT_LEN);
					break;
			}
			case 0x0E:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_REPEATER_STATION,value,HYDROLOGY_REPEATER_STATION_LEN);
					break;
			}
			case 0x0F:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_DEVICE_ID,value,HYDROLOGY_DEVICE_ID_LEN);
					break;
			}
			default:
			{
					ret = -1;
					break;
			}
	}
	return ret;
}

int hydrologyReadSelect(char* guide,char* value)
{
	int ret;
	
	switch(guide[0])
	{
			case 0x01:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_CENTER_ADDR,value,HYDROLOGY_CENTER_LEN);
					break;
			}
			case 0x02:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_REMOTE_ADDR,value,HYDROLOGY_REMOTE_LEN);
					break;
			}
			case 0x03:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_PASSWORD_ADDR,value,HYDROLOGY_PASSWORD_LEN);
					break;
			}
			case 0x04:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_CENTER1_ADDR,value,HYDROLOGY_CENTER1_ADDR_LEN);
					break;
			}
			case 0x05:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_BACKUP1_ADDR,value,HYDROLOGY_BACKUP1_ADDR_LEN);
					break;
			}
			case 0x06:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_CENTER2_ADDR,value,HYDROLOGY_CENTER2_ADDR_LEN);
					break;
			}
			case 0x07:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_BACKUP2_ADDR,value,HYDROLOGY_BACKUP2_ADDR_LEN);
					break;
			}
			case 0x08:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_CENTER3_ADDR,value,HYDROLOGY_CENTER3_ADDR_LEN);
					break;
			}
			case 0x09:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_BACKUP3_ADDR,value,HYDROLOGY_BACKUP3_ADDR_LEN);
					break;
			}
			case 0x0A:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_CENTER4_ADDR,value,HYDROLOGY_CENTER4_ADDR_LEN);
					break;
			}
			case 0x0B:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_BACKUP4_ADDR,value,HYDROLOGY_BACKUP4_ADDR_LEN);
					break;
			}
			case 0x0C:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WORK_MODE,value,HYDROLOGY_WORK_MODE_LEN);
					break;
			}
			case 0x0D:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ELEMENT_SELECT,value,HYDROLOGY_ELEMENT_SELECT_LEN);
					break;
			}
			case 0x0E:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_REPEATER_STATION,value,HYDROLOGY_REPEATER_STATION_LEN);
					break;
			}
			case 0x0F:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_DEVICE_ID,value,HYDROLOGY_DEVICE_ID_LEN);
					break;
			}
			default:
			{
					ret = -1;
					break;
			}
	}
	return ret;
}

int hydrologyBasicInfoConfig(void)
{
	int i = 0;
	int ret;

	hydrologyDownBody* pbody = (hydrologyDownBody*)(g_HydrologyMsg.downbody);

	for(i=0; i< pbody->count; i++)
	{
			ret = hydrologyConfigSelect((pbody->element)[i].guide, (pbody->element)[i].value);
			if(ret == -1)
					return i+1;
	}
	return 0;
}

int hydrologyBasicInfoRead(void)
{
//    int i = 0;
//    int ret;
//
//    hydrologyBody* pbody = (hydrologyBody*)(g_hydrologMsg.body);
//  
//    hydrologyDownConfigurationReadBody* downconfigurationreadbody = &(pbody->downConfigurationReadBody);
//
//    for(i=0; i< downconfigurationreadbody->count; i++)
//    {
//        ret = hydrologyReadSelect((downconfigurationreadbody->element)[i].guide, (downconfigurationreadbody->element)[i].value);
//        if(ret == -1)
//            return i+1;
//    }
	return 0;
}

int hydrologySetParaSelect(char* guide,char* value)
{
	int ret;
	
	switch(guide[0])
	{
			case 0x20:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_TIMER_INTERVAL,value,HYDROLOGY_TIMER_INTERVAL_LEN);
					break;
			}
			case 0x21:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_INTERVAL,value,HYDROLOGY_ADD_INTERVAL_LEN);
					break;
			}
			case 0x22:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_RAINFALL_BEGIN_TIME,value,HYDROLOGY_RAINFALL_BEGIN_TIME_LEN);
					break;
			}
			case 0x23:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_SAMPLE_INTERVAL,value,HYDROLOGY_SAMPLE_INTERVAL_LEN);
					break;
			}
			case 0x24:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_STORE_INTERVAL,value,HYDROLOGY_WATERLEVEL_STORE_INTERVAL_LEN);
					break;
			}
			case 0x25:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_RAINFALL_RESOLUTION,value,HYDROLOGY_RAINFALL_RESOLUTION_LEN);
					break;
			}
			case 0x26:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_RESOLUTION,value,HYDROLOGY_WATERLEVEL_RESOLUTION_LEN);
					break;
			}
			case 0x27:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_RAINFALL_ADD_THRESHOLD,value,HYDROLOGY_RAINFALL_ADD_THRESHOLD_LEN);
					break;
			}
			case 0x28:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE1,value,HYDROLOGY_WATERLEVEL_BASICVALUE1_LEN);
					break;
			}
			case 0x29:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE2,value,HYDROLOGY_WATERLEVEL_BASICVALUE2_LEN);
					break;
			}
			case 0x2A:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE3,value,HYDROLOGY_WATERLEVEL_BASICVALUE3_LEN);
					break;
			}
			case 0x2B:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE4,value,HYDROLOGY_WATERLEVEL_BASICVALUE4_LEN);
					break;
			}
			case 0x2C:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE5,value,HYDROLOGY_WATERLEVEL_BASICVALUE5_LEN);
					break;
			}
			case 0x2D:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE6,value,HYDROLOGY_WATERLEVEL_BASICVALUE6_LEN);
					break;
			}
			case 0x2E:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE7,value,HYDROLOGY_WATERLEVEL_BASICVALUE7_LEN);
					break;
			}
			case 0x2F:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE8,value,HYDROLOGY_WATERLEVEL_BASICVALUE8_LEN);
					break;
			}
			case 0x30:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE1,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE1_LEN);
					break;
			}
			case 0x31:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE2,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE2_LEN);
					break;
			}
			case 0x32:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE3,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE3_LEN);
					break;
			}
			case 0x33:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE4,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE4_LEN);
					break;
			}
			case 0x34:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE5,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE5_LEN);
					break;
			}
			case 0x35:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE6,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE6_LEN);
					break;
			}
			case 0x36:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE7,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE7_LEN);
					break;
			}
			case 0x37:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE8,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE8_LEN);
					break;
			}
			case 0x38:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_WATERLEVEL1,value,HYDROLOGY_ADD_WATERLEVEL1_LEN);
					break;
			}
			case 0x39:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_WATERLEVEL2,value,HYDROLOGY_ADD_WATERLEVEL2_LEN);
					break;
			}
			case 0x3A:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_WATERLEVEL3,value,HYDROLOGY_ADD_WATERLEVEL3_LEN);
					break;
			}
			case 0x3B:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_WATERLEVEL4,value,HYDROLOGY_ADD_WATERLEVEL4_LEN);
					break;
			}
			case 0x3C:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_WATERLEVEL5,value,HYDROLOGY_ADD_WATERLEVEL5_LEN);
					break;
			}
			case 0x3D:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_WATERLEVEL6,value,HYDROLOGY_ADD_WATERLEVEL6_LEN);
					break;
			}
			case 0x3E:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_WATERLEVEL7,value,HYDROLOGY_ADD_WATERLEVEL7_LEN);
					break;
			}
			case 0x3F:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_WATERLEVEL8,value,HYDROLOGY_ADD_WATERLEVEL8_LEN);
					break;
			}
			case 0x40:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_ABOVE_THRESHOLD,value,HYDROLOGY_ADD_ABOVE_THRESHOLD_LEN);
					break;
			}
			case 0x41:
			{
					ret = Hydrology_WriteStoreInfo(HYDROLOGY_ADD_BELOW_THRESHOLD,value,HYDROLOGY_ADD_BELOW_THRESHOLD_LEN);
					break;
			}
			default:
			{
					ret = -1;
					break;
			}
	}
	return ret;
}

int hydrologyReadParaSelect(char* guide,char* value)
{
	int ret;
	
	switch(guide[0])
	{
			case 0x20:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_TIMER_INTERVAL,value,HYDROLOGY_TIMER_INTERVAL_LEN);
					break;
			}
			case 0x21:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_INTERVAL,value,HYDROLOGY_ADD_INTERVAL_LEN);
					break;
			}
			case 0x22:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_RAINFALL_BEGIN_TIME,value,HYDROLOGY_RAINFALL_BEGIN_TIME_LEN);
					break;
			}
			case 0x23:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_SAMPLE_INTERVAL,value,HYDROLOGY_SAMPLE_INTERVAL_LEN);
					break;
			}
			case 0x24:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_STORE_INTERVAL,value,HYDROLOGY_WATERLEVEL_STORE_INTERVAL_LEN);
					break;
			}
			case 0x25:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_RAINFALL_RESOLUTION,value,HYDROLOGY_RAINFALL_RESOLUTION_LEN);
					break;
			}
			case 0x26:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_RESOLUTION,value,HYDROLOGY_WATERLEVEL_RESOLUTION_LEN);
					break;
			}
			case 0x27:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_RAINFALL_ADD_THRESHOLD,value,HYDROLOGY_RAINFALL_ADD_THRESHOLD_LEN);
					break;
			}
			case 0x28:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE1,value,HYDROLOGY_WATERLEVEL_BASICVALUE1_LEN);
					break;
			}
			case 0x29:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE2,value,HYDROLOGY_WATERLEVEL_BASICVALUE2_LEN);
					break;
			}
			case 0x2A:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE3,value,HYDROLOGY_WATERLEVEL_BASICVALUE3_LEN);
					break;
			}
			case 0x2B:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE4,value,HYDROLOGY_WATERLEVEL_BASICVALUE4_LEN);
					break;
			}
			case 0x2C:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE5,value,HYDROLOGY_WATERLEVEL_BASICVALUE5_LEN);
					break;
			}
			case 0x2D:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE6,value,HYDROLOGY_WATERLEVEL_BASICVALUE6_LEN);
					break;
			}
			case 0x2E:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE7,value,HYDROLOGY_WATERLEVEL_BASICVALUE7_LEN);
					break;
			}
			case 0x2F:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_BASICVALUE8,value,HYDROLOGY_WATERLEVEL_BASICVALUE8_LEN);
					break;
			}
			case 0x30:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE1,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE1_LEN);
					break;
			}
			case 0x31:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE2,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE2_LEN);
					break;
			}
			case 0x32:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE3,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE3_LEN);
					break;
			}
			case 0x33:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE4,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE4_LEN);
					break;
			}
			case 0x34:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE5,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE5_LEN);
					break;
			}
			case 0x35:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE6,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE6_LEN);
					break;
			}
			case 0x36:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE7,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE7_LEN);
					break;
			}
			case 0x37:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_WATERLEVEL_CORRECTVALUE8,value,HYDROLOGY_WATERLEVEL_CORRECTVALUE8_LEN);
					break;
			}
			case 0x38:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_WATERLEVEL1,value,HYDROLOGY_ADD_WATERLEVEL1_LEN);
					break;
			}
			case 0x39:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_WATERLEVEL2,value,HYDROLOGY_ADD_WATERLEVEL2_LEN);
					break;
			}
			case 0x3A:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_WATERLEVEL3,value,HYDROLOGY_ADD_WATERLEVEL3_LEN);
					break;
			}
			case 0x3B:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_WATERLEVEL4,value,HYDROLOGY_ADD_WATERLEVEL4_LEN);
					break;
			}
			case 0x3C:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_WATERLEVEL5,value,HYDROLOGY_ADD_WATERLEVEL5_LEN);
					break;
			}
			case 0x3D:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_WATERLEVEL6,value,HYDROLOGY_ADD_WATERLEVEL6_LEN);
					break;
			}
			case 0x3E:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_WATERLEVEL7,value,HYDROLOGY_ADD_WATERLEVEL7_LEN);
					break;
			}
			case 0x3F:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_WATERLEVEL8,value,HYDROLOGY_ADD_WATERLEVEL8_LEN);
					break;
			}
			case 0x40:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_ABOVE_THRESHOLD,value,HYDROLOGY_ADD_ABOVE_THRESHOLD_LEN);
					break;
			}
			case 0x41:
			{
					ret = Hydrology_ReadStoreInfo(HYDROLOGY_ADD_BELOW_THRESHOLD,value,HYDROLOGY_ADD_BELOW_THRESHOLD_LEN);
					break;
			}
			default:
			{
					ret = -1;
					break;
			}
	}
	return ret;
}

int hydrologySetPara(void)
{
	int i = 0;
	int ret;

	hydrologyDownBody* pbody = (hydrologyDownBody*)(g_HydrologyMsg.downbody);

	for(i=0; i< pbody->count; i++)
	{
			ret = hydrologySetParaSelect((pbody->element)[i].guide, (pbody->element)[i].value);
			if(ret == -1)
					return i+1;
	}
	return 0;
}

int hydrologyReadPara(void)
{
//    int i = 0;
//    int ret;
//
//    hydrologyBody* pbody = (hydrologyBody*)(g_hydrologMsg.body);
//  
//    hydrologyDownParameterReadBody* downparameterreadbody = &(pbody->downParameterReadBody);
//
//    for(i=0; i< downparameterreadbody->count; i++)
//    {
//        ret = hydrologyReadParaSelect((downparameterreadbody->element)[i].guide, (downparameterreadbody->element)[i].value);
//        if(ret == -1)
//            return i+1;
//    }
	return 0;
}

int Hydrology_SetPassword(void)
{
	hydrologyDownBody* pbody = (hydrologyDownBody*)(g_HydrologyMsg.downbody);

	Hydrology_WriteStoreInfo(HYDROLOGY_PASSWORD_ADDR,(pbody->element)[0].value,HYDROLOGY_PASSWORD_LEN);
		
	return 0;
}

int hydrologySetClock(void)
{
	hydrologyDownBody* pbody = (hydrologyDownBody*)(g_HydrologyMsg.downbody);

	Hydrology_SetTime((pbody->element)[0].value);
		
	return 0;
}

int hydrologySetICCard(void)
{
	hydrologyDownBody* pbody = (hydrologyDownBody*)(g_HydrologyMsg.downbody);

	Hydrology_WriteStoreInfo(HYDROLOGY_STATUS_ALARM_INFO,(pbody->element)[0].value,HYDROLOGY_STATUS_ALARM_INFO_LEN);
		
	return 0;
}

int hydrologyPump(void)
{
	hydrologyDownBody* pbody = (hydrologyDownBody*)(g_HydrologyMsg.downbody);

	Hydrology_WriteStoreInfo(HYDROLOGY_PUMP,(pbody->element)[0].value,HYDROLOGY_PUMP_LEN);
		
	return 0;
}

int hydrologyValve(void)
{
	hydrologyDownBody* pbody = (hydrologyDownBody*)(g_HydrologyMsg.downbody);

	Hydrology_WriteStoreInfo(HYDROLOGY_VALVE,(pbody->element)[0].value,HYDROLOGY_VALVE_LEN);
		
	return 0;
}

int hydrologyGate(void)
{
	char gatesize;
	hydrologyDownBody* pbody = (hydrologyDownBody*)(g_HydrologyMsg.downbody);
	
	gatesize = (pbody->element)[0].guide[0];
	gatesize = ((gatesize - 1)/8 + 1) + 2*gatesize + 1;
	Hydrology_WriteStoreInfo(HYDROLOGY_GATE,(pbody->element)[0].value,HYDROLOGY_GATE_LEN);
		
	return 0;
}

int hydrologyWaterSetting(void)
{
	hydrologyDownBody* pbody = (hydrologyDownBody*)(g_HydrologyMsg.downbody);

	Hydrology_WriteStoreInfo(HYDROLOGY_WATERSETTING,(pbody->element)[0].value,HYDROLOGY_WATERSETTING);
		
	return 0;
}

int HydrologyRecord(int index)
{
	uint16_t ERC_Couter = 0;
	int addr = (index - 1) * 2;
	char _temp_ERC_Couter[2];

	Hydrology_ReadStoreInfo(HYDROLOGY_RECORD + addr,_temp_ERC_Couter,2);
	ERC_Couter = (_temp_ERC_Couter[0] << 8) + _temp_ERC_Couter[1];
	ERC_Couter++;
	_temp_ERC_Couter[0] = ERC_Couter >> 8;
	_temp_ERC_Couter[1] = ERC_Couter & 0x00FF;
	Hydrology_WriteStoreInfo(HYDROLOGY_RECORD + addr,_temp_ERC_Couter,2);
			
	return 0;
}

int hydrologyCommand(int type)
{
	switch(type)
	{
			case Picture:
			{
//            Picture_Flag = 1;
					hydrologyChangeMode(M3);
					break;
			}        
			case ConfigurationModification:
			{
					hydrologyBasicInfoConfig();
					break;
			}
			case ConfigurationRead:
			{
					hydrologyBasicInfoRead();
					break;
			}
			case ParameterModification:
			{
					hydrologySetPara();
					HydrologyRecord(ERC2);
					break;
			}
			case ParameterRead:
			{
					hydrologyReadPara();
					break;
			}
			case InitializeSolidStorage:
			{
//            Store_SetInitializeSolidStorage();
					HydrologyRecord(ERC1);
					break;
			}
			case Reset:
			{
//            Store_SetInitializeSolidStorage();
					break;
			}        
			case ChangePassword:
			{
					Hydrology_SetPassword();
					HydrologyRecord(ERC5);
					break;
			}        
			case SetClock:
			{
					hydrologySetClock();
					break;
			}
			case SetICCard:
			{
					hydrologySetICCard();
					break;
			}
			case Pump:
			{
					hydrologyPump();
					break;
			}
			case Valve:
			{
					hydrologyValve();
					break;
			}        
			case Gate:
			{
					hydrologyGate();
					break;
			}
			case WaterSetting:
			{
					hydrologyWaterSetting();
					break;
			}        
	}
	return 0;
}




