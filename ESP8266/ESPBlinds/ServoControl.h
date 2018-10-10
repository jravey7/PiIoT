#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

enum ServoInteractionType
{
  NONE,
  OPEN_BLINDS,
  CLOSE_BLINDS,
  SET_OPEN,
  SET_CLOSE
};

struct ServoControl
{
    ServoInteractionType type;
    int setting;
};

enum ServoState
{
    SERVO_UNKNOWN,
    SERVO_OPEN,
    SERVO_CLOSED
};

struct ServoInfo
{
    int openSetting, closeSetting;
    ServoState curState;
};

#endif // SERVOCONTROL_H
