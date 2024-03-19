class LED {
	public:
		LED(unsigned int _pin);
		void on();
		void off();
		~LED();
	private:
		unsigned int pin;
};
