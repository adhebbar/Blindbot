/*
  A1-16.h - Modified for XYZrobot ATmega 1280 control board.
  Copyright (c) 2015 Wei-Shun You. XYZprinting Inc.  All right reserved.
*/
#include "Arduino.h"
#ifndef A1_16_h
#define A1_16_h
#define MAX_SERVOS                         20
#define BUFFER_SIZE                        64

#define A1_16_Broadcast_ID				   254

//Requested and ACK package CMD Definition
#define CMD_EEP_WRITE                      0x01
#define CMD_ACK_EEP_WRITE                  0x41
#define CMD_EEP_READ                       0x02
#define CMD_ACK_EEP_READ                   0x42
#define CMD_RAM_WRITE                      0x03
#define CMD_ACK_RAM_WRITE                  0x43
#define CMD_RAM_READ                       0x04
#define CMD_ACK_RAM_READ                   0x44
#define CMD_I_JOG                          0x05
#define CMD_ACK_I_JOG                      0x45
#define CMD_S_JOG                          0x06
#define CMD_ACK_S_JOG                      0x46
#define CMD_STAT                           0x07
#define CMD_ACK_STAT                       0x47
#define CMD_ROLLBACK                       0x08
#define CMD_ACK_ROLLBACK                   0x48
#define CMD_REBOOT                         0x09
#define CMD_ACK_REBOOT                     0x49

//EEPROM and RAM Parameter Definition
//EEPROM
#define EEP_Model_NO                       0x00		//  R/W,1 byte
#define EEP_Year                           0x01		//  R/W,1 byte
#define EEP_Month                          0x02		//  R/W,1 byte
#define EEP_Day                            0x03		//  R/W,1 byte
#define EEP_Auto_Rollback                  0x04		//  R/W,1 byte
#define EEP_Baud_Rate	                   0x05		//  R/W,1 byte
#define EEP_sID                            0x06		//  R/W,1 byte
#define EEP_ACK_Policy                     0x07		//  R/W,1 byte
#define EEP_Alarm_LED_Policy               0x08		//  R/W,1 byte
#define EEP_Toqure_Policy                  0x09		//  R/W,1 byte
#define EEP_SPDctl_Policy                  0x0a		//  R/W,1 byte
#define EEP_Max_TEMP                       0x0b		//  R/W,1 byte
#define EEP_Min_Voltage                    0x0c		//  R/W,1 byte
#define EEP_Max_Voltage                    0x0d		//  R/W,1 byte
#define EEP_ACC_Ratio                      0x0e		//  R/W,1 byte
#define EEP_Max_Wheel_Ref_POS              0x12		//  R/W,2 byte
#define EEP_Min_PWM                        0x15		//  R/W,1 byte
#define EEP_Max_PWM                        0x16		//  R/W,2 byte
#define EEP_Overload_PWM                   0x18		//  R/W,2 byte
#define EEP_Min_POS                        0x1A		//  R/W,2 byte
#define EEP_Max_POS                        0x1C		//  R/W,2 byte
#define EEP_POS_Kp                         0x1E		//  R/W,2 byte
#define EEP_POS_Kd                         0x20		//  R/W,2 byte
#define EEP_POS_Ki                         0x22		//  R/W,2 byte
#define EEP_CtoO_Ref_POS                   0x24		//  R/W,2 byte
#define EEP_OtoC_Ref_POS                   0x26		//  R/W,2 byte
#define EEP_Max_Current                    0x28		//  R/W,2 byte
#define EEP_Ramp_Speed                     0x2a		//  R/W,2 byte
#define EEP_LED_Blink_Period               0x2c		//  R/W,1 byte
#define EEP_Package_Timeout_Period         0x2e		//  R/W,1 byte
#define EEP_Overload_Dection_Period        0x30		//  R/W,1 byte
#define EEP_Inposition_Margin              0x32		//  R/W,1 byte
#define EEP_Over_Voltage_Dection_Period    0x33		//  R/W,1 byte
#define EEP_Over_Temp_Dection_Period       0x34		//  R/W,1 byte
#define EEP_Calibration_Difference         0x35		//  R/W,1 byte
//RAM
#define RAM_sID                            0x00		//  R/W,1 byte
#define RAM_ACK_Policy                     0x01		//  R/W,1 byte
#define RAM_Alarm_LED_Policy               0x02		//  R/W,1 byte
#define RAM_Toqure_Policy                  0x03		//  R/W,1 byte
#define RAM_SPDctl_Policy                  0x04		//  R/W,1 byte
#define RAM_Max_TEMP                       0x05		//  R/W,1 byte
#define RAM_Min_Voltage                    0x06		//  R/W,1 byte
#define RAM_Max_Voltage                    0x07		//  R/W,1 byte
#define RAM_ACC_Ratio                      0x08		//  R/W,1 byte
#define RAM_Max_Wheel_Ref_POS              0x0c		//  R/W,2 byte
#define RAM_Min_PWM                        0x0f		//  R/W,1 byte
#define RAM_Max_PWM                        0x10		//  R/W,2 byte
#define RAM_Overload_PWM                   0x12		//  R/W,2 byte
#define RAM_Min_POS                        0x14		//  R/W,2 byte
#define RAM_Max_POS                        0x16		//  R/W,2 byte
#define RAM_POS_Kp                         0x18		//  R/W,2 byte
#define RAM_POS_Kd                         0x1a		//  R/W,2 byte
#define RAM_POS_Ki                         0x1c		//  R/W,2 byte
#define RAM_CtoO_Ref_POS                   0x1e		//  R/W,2 byte
#define RAM_OtoC_Ref_POS                   0x20		//  R/W,2 byte
#define RAM_Max_Current                    0x22		//  R/W,2 byte
#define RAM_Ramp_Speed                     0x24		//  R/W,2 byte
#define RAM_LED_Blink_Period               0x26		//  R/W,1 byte
#define RAM_Package_Timeout_Period         0x28		//  R/W,1 byte
#define RAM_Overload_Dection_Period        0x2a		//  R/W,1 byte
#define RAM_Inposition_Margin              0x2c		//  R/W,1 byte
#define RAM_Over_Voltage_Dection_Period    0x2d		//  R/W,1 byte
#define RAM_Over_Temp_Dection_Period       0x2e		//  R/W,1 byte
#define RAM_Calibration_Difference         0x2f		//  R/W,1 byte
#define RAM_Status_Error                   0x30		//  R/W,1 byte
#define RAM_Status_Detail                  0x31		//  R/W,1 byte
#define RAM_LED_Control                    0x35		//  R/W,1 byte
#define RAM_Voltage                        0x36		//  RO,1 byte
#define RAM_Temp                           0x37		//  RO,1 byte
#define RAM_Current_Control_Mode           0x38		//  RO,1 byte
#define RAM_Tick                           0x39		//  RO,1 byte
#define RAM_Calibrated_Position            0x3a		//  RO,2 byte
#define RAM_Joint_Position                 0x3c		//  RO,2 byte
#define RAM_PWM_Output_Duty                0x40		//  RO,2 byte
#define RAM_Bus_Current                    0x42		//  RO,2 byte
#define RAM_Position_Goal                  0x44		//  RO,2 byte
#define RAM_Position_Ref                   0x46		//  RO,2 byte
#define RAM_Omega_Goal                     0x48		//  RO,2 byte
#define RAM_Omega_Ref                      0x4a		//  RO,2 byte
#define RAM_Requested_Counts               0x4c		//  RO,2 byte
#define RAM_ACK_Counts                     0x4e		//  RO,2 byte


//define packet basic parameter
#define MAX_PACKET_INDEX							64

#define PACKET_HEADER_ME							0xFF
#define PACKET_TAIL_ME								0xFE

#define ADDR_HEADER_ME								0x00
#define ADDR_LENGTH_ME								0x01
#define ADDR_CMD_ME										0x02

#define CMD_INI_CONN_ME								0x90
#define CMD_READ_PARAMETER_ME					0x91
#define CMD_SET_PARAMETER_ME					0x92
#define CMD_RELEASE_ME								0x93
#define CMD_REBOOT_ME									0x94
#define CMD_ROLLBACK_ME								0x95
#define CMD_SET_MOTOR_ME							0x96
#define CMD_READ_MOTOR_POSITION_ME		0x97
#define CMD_ERROR_RETURN_ME						0xF9

//define parameter of initialization connection
#define ADDR_INI_STATUS_ME						0x03
#define INI_STATUS_NONE_ME						0x00
#define INI_STATUS_ONE_ME							0x01
#define INI_STATUS_ERROR_ME						0x02

//define parameter of read command
#define ADDR_READ_PARAMETER_CODE_ME		0x03
#define ADDR_READ_PARAMETER_MSB_ME		0x04
#define ADDR_READ_PARAMETER_LSB_ME		0x05

//define parameter in set command
#define ADDR_SET_PARAMETER_CODE_ME		0x03
#define ADDR_SET_PARAMETER_MSB_ME			0x04
#define ADDR_SET_PARAMETER_LSB_ME			0x05
#define SET_PARAMETER_MAX_CODE				0X0F

//define parameter in position setting command
#define ADDR_MOTOR_POSITION_MSB				0X03
#define ADDR_MOTOR_POSITION_LSB				0X04

//define parameter in error return command
#define ADDR_ERROR_RETURN_CODE_ME			0x03
#define ERROR_RETURN_CMD_ME						0x00
#define ERROR_RETURN_TIMEOUT_ME				0x01
#define ERROR_RETURN_LENGTH_ME				0x02
#define ERROR_RETURN_OVER_RANGE_ME		0x03
#define ERROR_RETURN_LOST_CONN_ME			0x04

//define parameter write/read
#define PARA_CODE_sID_ME							0x01
#define PARA_CODE_ACK_POLICY_ME				0x02
#define PARA_CODE_LED_POLICY_ME				0x03
#define PARA_CODE_TOQ_POLICY_ME				0x04
#define PARA_CODE_MAX_TEMP_ME					0x05
#define PARA_CODE_MIN_VOLTAGE_ME			0x06
#define PARA_CODE_MAX_VOLTAGE_ME			0x07
#define PARA_CODE_MAX_LOAD_ME					0x08
#define PARA_CODE_Kp_ME								0x09
#define PARA_CODE_Ki_ME								0x0A
#define PARA_CODE_Kd_ME								0x0B
#define PARA_CODE_OVER_TEMP_ME				0x0C
#define PARA_CODE_OVER_VOLTAGE_ME			0X0D
#define PARA_CODE_OVER_LOAD_ME				0X0E
#define PARA_CODE_CALI_ANGLE_ME				0X0F

#define PARA_CODE_sID_MAX_ME					0xFD
#define PARA_CODE_ACK_POLICY_MAX_ME		0x02
#define PARA_CODE_LED_POLICY_MAX_ME		0x01
#define PARA_CODE_TOQ_POLICY_MAX_ME		0x01
#define PARA_CODE_MAX_TEMP_MAX_ME			0xFD
#define PARA_CODE_MIN_VOLTAGE_MAX_ME	0xFD
#define PARA_CODE_MAX_VOLTAGE_MAX_ME	0xFD
#define PARA_CODE_MAX_LOAD_MAX_ME			0x200
#define PARA_CODE_Kp_MAX_ME						0x7FFF
#define PARA_CODE_Ki_MAX_ME						0x7FFF
#define PARA_CODE_Kd_MAX_ME						0x7FFF
#define PARA_CODE_OVER_TEMP_MAX_ME		0xFF
#define PARA_CODE_OVER_VOLTAGE_MAX_ME	0xFF
#define PARA_CODE_OVER_LOAD_MAX_ME		0xFF
#define PARA_CODE_CALI_ANGLE_MAX_ME		0x1E		//absolute value

//define parameter read only
#define PARA_CODE_STATUS_ERROR_ME			0X10
#define PARA_CODE_STATUS_DETAIL_ME		0X11
#define PARA_CODE_PRESENT_TEMP_ME			0X12
#define PARA_CODE_PRESENT_VOLTAGE_ME	0X13
#define PARA_CODE_PRESENT_LOAD_ME			0X14

//define basic function
#define Enable_Timer4() TIMSK4 |= _BV(TOIE4)
#define Disable_Timer4() TIMSK4 &= ~_BV(TOIE4)
#define Reset_Timer4(t) TCNT4 = -t
#define TIMEOUT_LIMIT_ME							15625			// Ticks for 1 sec @16 MHz,prescale=1024
#define SERVO_CONN_CHECK_TIME					5					//check servo connected time

//define other parameter
#define A1_16_MODEL_NO								0x01
#define REBOOT_WAIT_TIME							2000
#define RESET_CHECK_TIMES							0X0A
#define MAX_WRITE_READ_CODE						0X0F


void A1_16_Ini(unsigned long baud);
void A1_16_SetPosition(unsigned char _pID, unsigned char _CMD,  unsigned char _playtime, unsigned int _position);
void A1_16_SetPos_serial(unsigned char _pID, unsigned char _CMD,  unsigned char _playtime, unsigned int _position, HardwareSerial& serial);
void A1_16_SetSpeed(unsigned char _pID, unsigned char _playtime, int _speed);
void A1_16_TorqueOff(unsigned char _pID);
int A1_16_ReadData(unsigned char _pID, unsigned char _CMD, unsigned char _addr_start, unsigned char _data_length);
int A1_16_ReadData_s(unsigned char _pID, unsigned char _CMD, unsigned char _addr_start, unsigned char _data_length, HardwareSerial& serial);
int A1_16_ReadPacket(unsigned char _data_length);
int A1_16_ReadPacket(unsigned char _data_length, HardwareSerial &serial);
void A1_16_WriteData(unsigned char _pID, unsigned char _CMD, unsigned char _addr_start, char _data_write);
void A1_16_WriteData2(unsigned char _pID, unsigned char _CMD, unsigned char _addr_start, int _data_write);
void A1_16_Basic(unsigned char _pID, unsigned char _CMD);


#define SetPositionS_JOG(id, time, pos) (A1_16_SetPosition(id, CMD_S_JOG,  time, pos))
#define SetPositionI_JOG(id, time, pos) (A1_16_SetPosition(id, CMD_I_JOG,  time, pos))

#define ReadDataEEP1(id, _addr) A1_16_ReadData(id, CMD_EEP_READ, _addr, 0x01)
#define ReadDataEEP2(id, _addr) A1_16_ReadData(id, CMD_EEP_READ, _addr, 0x02)
#define ReadDataRAM1(id, _addr) A1_16_ReadData(id, CMD_RAM_READ, _addr, 0x01)
#define ReadDataRAM2(id, _addr) A1_16_ReadData(id, CMD_RAM_READ, _addr, 0x02)
#define ReadPosition(id) A1_16_ReadData(id, CMD_RAM_READ, RAM_Joint_Position, 0x02)
#define ReadPosition_serial(id, serial) A1_16_ReadData_s(id, CMD_RAM_READ, RAM_Joint_Position, 0x02, serial)


#define WriteDataEEP1(id, _addr, _data) A1_16_WriteData(id, CMD_EEP_WRITE, _addr, _data)
#define WriteDataRAM1(id, _addr, _data) A1_16_WriteData(id, CMD_RAM_WRITE, _addr, _data)
#define WriteDataEEP2(id, _addr, _data) A1_16_WriteData2(id, CMD_EEP_WRITE, _addr, _data)
#define WriteDataRAM2(id, _addr, _data) A1_16_WriteData2(id, CMD_RAM_WRITE, _addr, _data)
#define SetID(id, newid) A1_16_WriteData(id, CMD_EEP_WRITE, EEP_sID, newid)
#define SetKpRAM(id, Kp) A1_16_WriteData2(id, CMD_RAM_WRITE, RAM_POS_Kp, Kp)
#define SetKdRAM(id, Kd) A1_16_WriteData2(id, CMD_RAM_WRITE, RAM_POS_Kd, Kd)
#define SetKiRAM(id, Ki) A1_16_WriteData2(id, CMD_RAM_WRITE, RAM_POS_Ki, Ki)
#define SetRampSpeedRAM(id, RampSpeed) A1_16_WriteData2(id, CMD_RAM_WRITE, RAM_Ramp_Speed, RampSpeed)

#define ReadStatus(id) A1_16_Basic(id, CMD_STAT)
#define RollBack(id) A1_16_Basic(id, CMD_ROLLBACK)
#define RollBackAll() A1_16_Basic(254, CMD_ROLLBACK)
#define Reboot(id) A1_16_Basic(id, CMD_REBOOT)
#define RebootAll() A1_16_Basic(254, CMD_REBOOT)

#endif
