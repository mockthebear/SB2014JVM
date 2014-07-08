class t6 {

	public static void main(String[] args) {
		shiftTest(0xff00ff00, 3);
		shiftTest(0xff00ff00ff00ff00L, 3);
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
