/******************************************************************************
Copyright (C), CETE38
�ļ���  :    PackCommandID.h
����    :    �ƹ��
�汾    :    v0.0.1
�������:    2013-03-01
����    :    PackCommandID.h����ͨ�����ݰ��������ʶ�����Ϊ��Ϣ��ǩ��
                        ÿ����Ϣ��ǩ��Ψһ���ʾ����ӦΨһ�������������Ӧ�����֪ͨ����
����    :
��ʷ��¼:
1.
�޸�����:
����    :
�޸�����:
2.
...
******************************************************************************/
#ifndef PACK_COMMANDID_H
#define PACK_COMMANDID_H
//�����������ʶ
const unsigned short CONNECT_REQUEST_PACK = 0X0001;
//�Ͽ��������ʶ
const unsigned short DISCONNECT_REQUEST_PACK = 0X0002;
//ͨ����·�����������ʶ
const unsigned short LINKTEST_REQUEST_PACK = 0X0003;
//Ŀ��ϵͳ����������ʶ
const unsigned short TARGET_CHECK_REQUEST_PACK = 0X0010;
//Ŀ���ѡ���������ʶ
const unsigned short TARGET_SELECT_REQUEST_PACK = 0X0011;
//�������ڵ���
const unsigned short SINGLE_CORE_STEP_CYCLE=0x0020;
//����ָ���
const unsigned short SINGLE_CORE_STEP_INST=0x0021;
//���˼�������
const unsigned short SINGLE_CORE_RUN=0x0022;
//������ͣ
const unsigned short SINGLE_CORE_PAUSE=0x0023;
//���˸�λ
const unsigned short SINGLE_CORE_RESET=0x0024;
//����JTAG��λ
const unsigned short SINGLE_JTAG_RESET=0x0025;


//�������
const unsigned short MULTI_CORE_STEP_CYCLE=0x0030;
//�������
const unsigned short MULTI_CORE_RUN=0x0032;
//���ͬ��ֹͣ
const unsigned short MULTI_CORE_PAUSE=0x0033;
//���ͬ����λ
const unsigned short MULTI_CORE_RESET=0x0034;
//���ͬ��JTAG��λ
const unsigned short MULTI_CORE_JTAG_RESET=0x0035;

//���Ĵ���
const unsigned short READ_REGISTER=0x0040;
//д�Ĵ���
const unsigned short WRITE_REGISTER=0x0041;
//���洢��
const unsigned short READ_MEMORY=0x0042;
//д�Ĵ���
const unsigned short WRITE_MEMORY=0x0043;
//���Ĵ�������ɢ��
const unsigned short READ_MEMORY_DISCRETE=0x0044;
//д�洢������ɢ��
const unsigned short WRITE_MEMORY_DISCRETE=0x0045;

//��JTAG�Ĵ���
const unsigned short WRITE_JTAG_REGISTER=0x0050;
//дJTAG�Ĵ���
const unsigned short READ_JTAG_REGISTER=0x0051;

//���öϵ�
const unsigned short BREAKPOINT_INSERT=0x0060;
//����ϵ�
const unsigned short CLEAR_BREAKPOINT=0x0061;
//���ù۲��
const unsigned short WATCHPOINT_INSERT=0x0062;
//����۲��
const unsigned short CLEAR_WATCHPOINT=0x0063;


//����JTAGʱ��Ƶ��
const unsigned short SET_JTAG_FREQUENCY=0x00E0;

//���ģ����ר������
const unsigned short SIMULATOR_SPEC_COMMAND=0xff;

//ֹͣ�¼�֪ͨ����ʶ
const unsigned short STOP_EVENT_NOTIFY_PACK = 0X00F0;



#endif//PACK_COMMANDID_H
