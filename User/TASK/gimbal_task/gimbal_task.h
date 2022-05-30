#ifndef __GIMBAL_TASK_H
#define __GIMBAL_TASK_H

#include "main.h"
#include "CAN_Receive.h"
#include "pid.h"
#include "RC_DT7.h"
#include "miniPC.h"
#include "user_lib.h"
#include "motor_control.h"
#include "INS_task.h"

//�����ʼ�� ����һ��ʱ��
#define GIMBAL_TASK_INIT_TIME 201
//��̨����������
#define GIMBAL_CONTROL_TIME_MS 1

/******�����ػ�е�Ƕ� �������ʱ��Ҫdebug�޸ģ�����******************/
#define YAW_ECD_DEL		6136//655			//��̨����ʱ����Ļ�е�Ƕ�
#define PITCH_ECD_MAX	5966//3811
#define PITCH_ECD_MIN	4565//2036
#define PITCH_ECD_DEL	5412//2696
/*******************��ػ�е�Ƕ�_END**********************************/

//yaw��pitch�Ƕ���ң�����������
#define YAW_RC_SEN		-0.000003f
#define PITCH_RC_SEN	-0.000003f
//����������
#define YAW_MOUSE_SEN	0.000001f
#define PITCH_MOUSE_SEN	-0.000001f
//���������������
#define YAW_AUTO_SEN    0.15f//0.0055f//-0.0055f
#define PITCH_AUTO_SEN  0.14f//0.0044f//-0.07f //0.005
//��̨�����ٶ�
#define GIMBAL_RETURN_PITCH	0.0008f
#define GIMBAL_RETURN_YAW	0.001f//0.0008f
//�˲�ϵ��
#define GIMBAL_YAW_ACCEL_NUM	0.1666666667f
#define GIMBAL_PITCH_ACCEL_NUM	0.3333333333f
//GM6020���CAN���͵�ѹ
#define MAX_GM6020_CAN_VOLTAGE	30000.0f

/***********************PID***************************/
/*PID����ģ��
{
	KP,
	KI,
	KD,
	OUT_MAX,
	IOUT_MAX
}*/
//yaw   ң�� ��еģʽ �ٶȻ�(�ڻ�)
#define YAW_ECD_SPEED_RC_PID_Init	1500.0f, 0.0f, 0.5f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//yaw   ң�� ��еģʽ �ǶȻ�(�⻷)
#define YAW_ECD_ANGLE_RC_PID_Init	178.0f, 0.0f, 0.0f, 10.0f, 0.0f
//yaw   ң�� ������ģʽ �ٶȻ�(�ڻ�)
#define YAW_GYRO_SPEED_RC_PID_Init	1000.0f, 0.0f, 0.5f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//yaw   ң�� ������ģʽ �ǶȻ�(�⻷)
#define YAW_GYRO_ANGLE_RC_PID_Init	110.0f, 0.0f, 0.0f, 10.0f, 0.0f
//pitch ң�� ��еģʽ �ٶȻ�(�ڻ�)
#define PITCH_ECD_SPEED_RC_PID_Init	1000.0f, 0.0f, 2.0f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//pitch ң�� ��еģʽ �ǶȻ�(�⻷)
#define PITCH_ECD_ANGLE_RC_PID_Init	200.0f, 0.0f, 0.0f, 10.0f, 0.0f
//pitch ң�� ������ģʽ �ٶȻ�(�ڻ�)
#define PITCH_GYRO_SPEED_RC_PID_Init	1000.0f, 0.0f, 2.0f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//pitch ң�� ������ģʽ �ǶȻ�(�⻷)
#define PITCH_GYRO_ANGLE_RC_PID_Init	150.0f, 0.0f, 0.0f, 10.0f, 0.0f
/*****************************����Ϊ�ֶ������µ�PID����*****************************/
//yaw   ң�� ��еģʽ �ٶȻ�(�ڻ�)
#define YAW_ECD_SPEED_MOUSE_PID_Init	1500.0f, 0.0f, 0.5f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//yaw   ң�� ��еģʽ �ǶȻ�(�⻷)
#define YAW_ECD_ANGLE_MOUSE_PID_Init	178.0f, 0.0f, 0.0f, 10.0f, 0.0f
//yaw   ң�� ������ģʽ �ٶȻ�(�ڻ�)
#define YAW_GYRO_SPEED_MOUSE_PID_Init	1000.0f, 0.0f, 0.5f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//yaw   ң�� ������ģʽ �ǶȻ�(�⻷)
#define YAW_GYRO_ANGLE_MOUSE_PID_Init	100.0f, 0.0f, 0.0f, 10.0f, 0.0f
//pitch ң�� ��еģʽ �ٶȻ�(�ڻ�)
#define PITCH_ECD_SPEED_MOUSE_PID_Init	1000.0f, 0.0f, 2.0f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//pitch ң�� ��еģʽ �ǶȻ�(�⻷)
#define PITCH_ECD_ANGLE_MOUSE_PID_Init	200.0f, 0.0f, 0.0f, 10.0f, 0.0f
/*****************************����Ϊ�������µ�PID����*****************************/
//yaw ���� ��еģʽ �ٶȻ�(�ڻ�)
#define YAW_ECD_SPEED_AUTO_PID_Init	1500.0f, 0.0f, 0.5f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//yaw ���� ��еģʽ �ǶȻ�(�⻷)
#define YAW_ECD_ANGLE_AUTO_PID_Init	178.0f, 0.0f, 0.0f, 10.0f, 0.0f
//yaw ���� ������ģʽ �ٶȻ�(�ڻ�)
#define YAW_GYRO_SPEED_AUTO_PID_Init	1500.0f, 0.0f, 0.5f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//yaw ���� ������ģʽ �ǶȻ�(�⻷)
#define YAW_GYRO_ANGLE_AUTO_PID_Init	120.0f, 0.0f, 0.5f, 10.0f, 0.0f
//pitch ���� ��еģʽ �ٶȻ�(�ڻ�)
#define PITCH_ECD_SPEED_AUTO_PID_Init	1000.0f, 0.0f, 2.0f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//pitch ���� ��еģʽ �ǶȻ�(�⻷)
#define PITCH_ECD_ANGLE_AUTO_PID_Init	150.0f, 0.0f, 0.0f, 10.0f, 0.0f
//pitch ���� ������ģʽ �ٶȻ�(�ڻ�)
#define PITCH_GYRO_SPEED_AUTO_PID_Init	1000.0f, 0.0f, 2.0f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
//pitch ���� ������ģʽ �ǶȻ�(�⻷)
#define PITCH_GYRO_ANGLE_AUTO_PID_Init	150.0f, 0.0f, 0.0f, 10.0f, 0.0f
/*****************************����Ϊ�Զ������µ�PID����*****************************/
//С����ģʽ ң�� �ٶȻ�(�ڻ�)
#define YAW_gyromode_SPEED_RC_PID_Init	1000.0f, 0.0f, 2.0f, MAX_GM6020_CAN_VOLTAGE, 5000.0f 
//������ģʽ ң�� �ǶȻ�(�⻷)
#define YAW_gyromode_ANGLE_RC_PID_Init	150.0f, 0.0f, 0.0f, 10.0f, 0.0f
//С����ģʽ ���� �ٶȻ�(�ڻ�)
#define YAW_gyromode_SPEED_AUTO_PID_Init	1000.0f, 0.0f, 2.0f, MAX_GM6020_CAN_VOLTAGE, 5000.0f 
//������ģʽ ���� �ǶȻ�(�⻷)
#define YAW_gyromode_ANGLE_AUTO_PID_Init	150.0f, 0.0f, 0.0f, 10.0f, 0.0f
/*****************************����ΪС����ģʽ��YAW���PID����*****************************/
//yaw���
#define YAW_buff_anti_SPEED_PID_Init	1500.0f, 0.0f, 0.5f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
#define YAW_buff_anti_ANGLE_PID_Init	178.0f, 0.0f, 0.0f, 10.0f, 0.0f
//pitch 
#define PITCH_buff_anti_SPEED_PID_Init	1000.0f, 0.0f, 2.0f, MAX_GM6020_CAN_VOLTAGE, 5000.0f
#define PITCH_buff_anti_ANGLE_PID_Init	200.0f, 0.0f, 0.0f, 10.0f, 0.0f
/*****************************����Ϊ���ģʽ�µ�PID����*****************************/
/**********************PID_END************************/
typedef enum
{
	GIMBAL_RELAX,				//��̨����
	GIMBAL_GYRO,				//�����ǽǶȿ���
	GIMBAL_ENCONDE,				//�������������
	GIMBAL_CALI					//��̨У׼
}Gimbal_Mode_e;
typedef enum
{
	GIMBAL_NORMAL,				//��̨��ͨ
	GIMBAL_NORMAL_GR,			//����С��������̨��ͨ
	GIMBAL_AUTO,				//��̨����
	GIMBAL_AUTO_GR,				//����С��������̨����
	GIMBAL_CENTER,				//��̨����
	GIMBAL_TURN,				//��̨��ͷ
	GIMBAL_STOP,				//��ֹ̨ͣ
	GIMBAL_BUFF_ANTI			//���
}Gimbal_Behavior_e;
typedef struct
{
	const motor_measure_t *gimbal_motor_measure;	//���������Ϣ
	first_order_filter_type_t gimbal_motor_first_OF;	//���һ�׵�ͨ�˲�
	
	//�ɵ�������Ƕ�
	fp32 relative_angle;
	fp32 relative_angle_last;
	fp32 relative_angle_set;
	//�����Ƿ����Ƕ� rad
	fp32 absolute_angle;			
	fp32 absolute_angle_set;
	fp32 absolute_angle_last;
	
	fp32 offset_angle;		//
	
	fp32 speed;				//��ǰ���ٶ�rad/s
	fp32 speed_set;			//�趨���ٶ�

	uint16_t ecd_last;		//��һ�ε��������е�Ƕ�ԭʼ����
	fp32 gyro_last;			//��һ��������ԭʼ���� -2PI~2PI rad
	fp32 ecd_now;			//��ǰת����ĽǶ� -2PI~2PI rad
	fp32 gyro_now;			//��ǰת����ĽǶ� -2PI~2PI rad
	
	fp32 voltage_set;
	int16_t voltage_give_last;
	int16_t voltage_give;	//���͵ĵ�ѹֵ
	
	uint8_t ecd_turn_table;//�Ƕ������� 1Ϊ�� 0Ϊ��
	uint8_t gyro_turn_table;//�Ƕ������� 1Ϊ�� 0Ϊ��
	//uint8_t turn_table_flag;//�Ƕ������� 1Ϊ�� 0Ϊ��
} Gimbal_Motor_s;
typedef struct
{
	const RC_ctrl_s *gimbal_RC;				//��̨ʹ�õ�ң����ָ��
	Auto_Gimbal_Ctrl_t *gimbal_AUTO_ctrl;	//����Ƕ�����
	const INS_Data_s *ins_data;			//��������ؽǶ�
	
	Control_Mode_e ctrl_mode;				//����ģʽ
	Gimbal_Mode_e gimbal_mode;				//��̨ģʽ
	Gimbal_Behavior_e gimbal_behavior;		//��̨��Ϊ
	Vision_Mode_e vision_mode;				//����ģʽ
	Gimbal_Mode_e gimbal_mode_last;			//��̨��һ��ģʽ
	Gimbal_Behavior_e gimbal_behavior_last;		//��̨��Ϊ
	
	Gimbal_Motor_s pitch_motor;				//��̨pitch���
	Gimbal_Motor_s yaw_motor;				//��̨yaw���
	
	int16_t turn_circle_num;
	uint8_t turn_mid_flag;
}Gimbal_Control_s;


extern const Gimbal_Motor_s *get_gimbal_yaw_motor_point(void);
extern const Gimbal_Motor_s *get_gimbal_pitch_motor_point(void);
extern Vision_Mode_e get_vision_mode(void);
extern fp32 get_gimbal_relative_angle(void);
extern void GIMBAL_task(void *pvParameters);
fp32 get_gimbal_pitch_offset_angle(void);
fp32 get_gimbal_yaw_offset_angle(void);
const PidTypeDef *get_yaw_angle_pid_angle(void);
const PidTypeDef *get_yaw_speed_pid_angle(void);
#endif
