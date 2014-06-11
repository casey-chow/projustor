#include <Servo.h>

class ProjustorServo
{
	public:
		ProjustorServo(int pin);
                void MoveObjToPos(long newPosition, long height);
                void MoveObjToAng(int newAng);
		long objPosition(void);
	private:
		int _pin; //pin number of Arduino that is connected with SIG pin of servo
                
                Servo servo;
};
