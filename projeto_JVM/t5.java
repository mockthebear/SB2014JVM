class t5 {

	public static void main(String[] args) {
		byte a, b;
		
		a = 10;
		b = 4;
		cmpTest(a, b);
		cmpTest(-a, b);
		cmpTest(a, -b);
		cmpTest(-a, -b);
		
		a = 11;
		b = 25;
		cmpTest(a, b);
		cmpTest(-a, b);
		cmpTest(a, -b);
		cmpTest(-a, -b);
		
		a = 7;
		b = 7;
		cmpTest(a, b);
		cmpTest(-a, b);
		cmpTest(a, -b);
		cmpTest(-a, -b);
		/*
		a = +0.0;
		b = -0.0;
		cmpTest(a, b);
		cmpTest(-a, b);
		cmpTest(a, -b);
		cmpTest(-a, -b);
		*/
		///*
		a = (byte)0x5544456;
		b = (byte)0x4554111;
		cmpTest(a, b);
		cmpTest(-a, b);
		cmpTest(a, -b);
		cmpTest(-a, -b);
		//*/
	}
	static void cmpTest(int a, int b) {
		System.out.println(a);
		System.out.println(b);
		if(a==b)
			System.out.println("a == b");
		if(a!=b)
			System.out.println("a != b");
		if(a>b)
			System.out.println("a > b");
		if(a<b)
			System.out.println("a < b");
		if(a>=b)
			System.out.println("a >= b");
		if(a<=b)
			System.out.println("a <= b");
		
		System.out.println();
	}
	static void cmpTest(long a, long b) {
		System.out.println(a);
		System.out.println(b);
		if(a==b)
			System.out.println("a == b");
		if(a!=b)
			System.out.println("a != b");
		if(a>b)
			System.out.println("a > b");
		if(a<b)
			System.out.println("a < b");
		if(a>=b)
			System.out.println("a >= b");
		if(a<=b)
			System.out.println("a <= b");
		
		System.out.println();
	}
	static void cmpTest(float a, float b) {
		System.out.println(a);
		System.out.println(b);
		if(a==b)
			System.out.println("a == b");
		if(a!=b)
			System.out.println("a != b");
		if(a>b)
			System.out.println("a > b");
		if(a<b)
			System.out.println("a < b");
		if(a>=b)
			System.out.println("a >= b");
		if(a<=b)
			System.out.println("a <= b");
		
		System.out.println();
	}
	static void cmpTest(double a, double b) {
		System.out.println(a);
		System.out.println(b);
		if(a==b)
			System.out.println("a == b");
		if(a!=b)
			System.out.println("a != b");
		if(a>b)
			System.out.println("a > b");
		if(a<b)
			System.out.println("a < b");
		if(a>=b)
			System.out.println("a >= b");
		if(a<=b)
			System.out.println("a <= b");
		
		System.out.println();
	}
	static void cmpTest(short a, short b) {
		System.out.println(a);
		System.out.println(b);
		if(a==b)
			System.out.println("a == b");
		if(a!=b)
			System.out.println("a != b");
		if(a>b)
			System.out.println("a > b");
		if(a<b)
			System.out.println("a < b");
		if(a>=b)
			System.out.println("a >= b");
		if(a<=b)
			System.out.println("a <= b");
		
		System.out.println();
	}
	static void cmpTest(byte a, byte b) {
		System.out.println(a);
		System.out.println(b);
		if(a==b)
			System.out.println("a == b");
		if(a!=b)
			System.out.println("a != b");
		if(a>b)
			System.out.println("a > b");
		if(a<b)
			System.out.println("a < b");
		if(a>=b)
			System.out.println("a >= b");
		if(a<=b)
			System.out.println("a <= b");
		
		System.out.println();
	}
}
