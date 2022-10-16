class MyClass
{
	void runTests()
	{
		doStuff();
	}

	const int gimmieDatInt()
	{
		int i = 0;

		auto nice = [this]() { doMore(); };
		nice();
	}
}

namespace MySpace 
{
	struct Data{
		int i = 0;
		void do_a_lot()
		{
			i = 100;
		}
	}

	class NiceClass
	{
	public:
		run();

	private:
		int fesa = 0;
	}
}