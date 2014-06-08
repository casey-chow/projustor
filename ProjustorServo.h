class ProjustorServo
{
	public:
		ProjustorServo(int pin);
                void MoveObj(void);
		long objPosition(void);
	private:
		int _pin; //pin number of Arduino that is connected with SIG pin of servo
                long _position; // position of the servo
                
                int pulseLength(long tgtPosition); // get pulse length 
};
