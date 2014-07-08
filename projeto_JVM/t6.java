class t6 {

	public static void main(String[] args) {
		shiftTest((byte)0xffd83785, 3);
		shiftTest((short)0xffd6a785, 3);
		shiftTest(0xff00ff00, 3);
		shiftTest(0xff00ff00ff00ff00L, 3);
	}
	static void shiftTest(byte a, int b) {

		System.out.println(a<<b);
		System.out.println(a>>b);
		System.out.println(a>>>b);
		
		
		System.out.println();
	}
	static void shiftTest(short a, int b) {

		System.out.println(a<<b);
		System.out.println(a>>b);
		System.out.println(a>>>b);
		
		
		System.out.println();
	}
	static void shiftTest(int a, int b) {

		System.out.println(a<<b);
		System.out.println(a>>b);
		System.out.println(a>>>b);
		
		
		System.out.println();
	}
	static void shiftTest(long a, long b) {

		System.out.println(a<<b);
		System.out.println(a>>b);
		System.out.println(a>>>b);
		
		
		System.out.println();
	}
}
