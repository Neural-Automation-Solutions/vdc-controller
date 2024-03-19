class Switch {
	public:
		Switch(unsigned int _pin);
		~Switch();
	private:
		unsigned int pin;
		static void callbackFunc(
			int gpio,
			int level,
			unsigned int tick
			);
};
