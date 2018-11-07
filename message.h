
#ifndef __MESSAGE_H
#define __MESSAGE_H

//#include "stm32l4xx_hal.h"

#define MAX_ELEMENT                     16

#define M1                              1
#define M2                              2
#define M3                              3
#define M4                              4

#define SOH1                            0x7E
#define SOH2                            0x7E
#define STX                             0x02
#define SYN                             0x16
#define ETX                             0x03
#define ETB                             0x17
#define ENQ                             0x05
#define EOT                             0x04
#define ACK                             0x06
#define NAK                             0x15
#define ESC                             0x1B

#define ANALOG                          1
#define PULSE                           2
#define SWITCH                          3

#define ELEMENT_REGISTER(id,type,D,d) {id,type,D,d}

#define ERC1                            1
#define ERC2                            2
#define ERC3                            3
#define ERC4                            4
#define ERC5                            5
#define ERC6                            6
#define ERC7                            7
#define ERC8                            8
#define ERC9                            9
#define ERC10                           10
#define ERC11                           11
#define ERC12                           12
#define ERC13                           13
#define ERC14                           14
#define ERC15                           15
#define ERC16                           16
#define ERC17                           17
#define ERC18                           18
#define ERC19                           19

typedef enum taghydrologyBodyType
{
	LinkMaintenance = 0,//ң��վ��·ά�ֱ�
	Test,//ң��վ���Ա�
	EvenPeriodInformation,//����ʱ��ˮ����Ϣ��
	TimerReport,//ң��վ��ʱ��
	AddReport,//ң��վ�ӱ���
	Hour,//ң��վСʱ��
	ArtificialNumber,//ң��վ�˹�������
	Picture,//ң��վͼƬ��
	Realtime,//����վ��ѯң��վʵʱ����
	Period,//����վ��ѯң��վʱ������
	InquireArtificialNumber,//����վ��ѯң��վ�˹�����
	SpecifiedElement,//����վ��ѯң��վָ��Ҫ��ʵʱ����
	ConfigurationModification,//ң��վ�����޸�
	ConfigurationRead,//ң��վ���ö�ȡ
	ParameterModification,//����վ�޸�ң��վ���в���
	ParameterRead,//����վ��ȡң��վ���в���
	WaterPumpMotor,//����վ��ѯˮ�õ��ʵʱ��������
	SoftwareVersion,//����վ��ѯң��վ��ѯң��վ����汾
	Status,//����վ��ѯң��վ״̬��Ϣ
	InitializeSolidStorage,//��ʼ����̬�洢����
	Reset,//�ָ�ң��վ��������
	ChangePassword,//����վ�޸Ĵ�������
	SetClock,//����վ����ң��վʱ��
	SetICCard,//����վ����ң��վIC��״̬
	Pump,//����վ����ң��վˮ�ÿ���������Ӧ/ ˮ��״̬�Ա�
	Valve,//����վ����ң��վ���Ʒ��ſ���������Ӧ/ ����״̬�Ա�
	Gate,//����վ����ң��վ����բ�ſ���������Ӧ/ բ��״̬��Ϣ�Ա�
	WaterSetting,//����վ����ң��վˮ����ֵ����������Ӧ
	Record,//����վ��ѯң��վ�¼���¼
	Time,//����վ��ѯң��վʱ��
	BodyTypeEnd
    
}hydrologyBodyType;

#pragma pack(1)
//Ҫ�ػ�������
typedef struct tagHydrologyElement
{
	char guide[2];
	char num;
	char* value;
}hydrologyElement;

typedef struct tagHydrologyElementInfo
{
	char ID;
	char type;
	char D;
	char d;
}hydrologyElementInfo;

//ң��վ���б��ı�ͷ�ṹ
typedef struct taghydrologyHeader
{
	char framestart[2];
	char centeraddr;
	char remoteaddr[5];
	char password[2];
	char funcode;
	char dir_len[2];
	char paketstart;
	char count_seq[3];
}hydrologyHeader;

//ң��վ���б������Ľṹ
typedef struct tagHydrologyUpBody
{
  char streamid[2];
  char sendtime[6];
  char rtuaddrid[2];
  char rtuaddr[5];
  char rtutype;
  char observationtimeid[2];
  char observationtime[5];
  int count;
  hydrologyElement element[MAX_ELEMENT];
  int len;
}hydrologyUpBody;

//ң��վ���б������Ľṹ
typedef struct tagHydrologyDownBody
{
  char streamid[2];
  char sendtime[6];
  char rtuaddrid[2];
  char rtuaddr[5];
  int count;
  hydrologyElement element[MAX_ELEMENT];
  int len;
}hydrologyDownBody;

typedef struct tagpacket
{
	void* header;
	void* upbody;
	void* downbody;
	char end;
	short crc16;
	int len;
}packet;

#pragma pack()


void Hydrology_ReadPassword(char* password);

void Hydrology_ReadCenterAddr(char* centeraddr);

void Hydrology_ReadRemoteAddr(char* remoteaddr);

void Hydrology_ReadTime(char* time);

void Hydrology_SetTime(char* time);

void Hydrology_ReadRTUType(char* type);

void Hydrology_ReadObservationTime(char* observationtime,int index);

int Hydrology_ReadStoreInfo(long addr,char *data,int len);

int Hydrology_WriteStoreInfo(long addr,char *data,int len);

short hydrologyCRC16(char* pchMsg, int wDataLen);

int hydrologyProcess(char funcode);
	
extern hydrologyHeader g_HydrologyUpHeader;
extern hydrologyHeader g_HydrologyDownHeader;
extern packet g_HydrologyMsg;
#endif
