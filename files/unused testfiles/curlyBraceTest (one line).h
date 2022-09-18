
namespace TestSpace {
	struct Foo
	{
		void doStuff()
		{
			int i = 0;
			return i + 100;
		}
		void doLambda()
		{
			auto l = [this](){return;};
			l();
		}
		void doLongLambda()
		{
			auto l = [this]()
			{
				c + 3.62;
				return;
			};

			l();
		}


		static void doStaticStuff() {}
	}
}

static void calculateStuff(){
	return a * b;
}