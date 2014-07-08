class T3 {
	static final int max = 20;
	public static void main(String[] args) {
		shortTest();
	}
	
	static void intTest() {
		int[] a = new int[max];
		int b = 0,
			c = 2;
		
		for(int i=0; i<max; i++) {
			a[i] = b;
			b = b + c;
		}
		for(int i=0; i<max; i++) {
			System.out.println(a[i]);
		}
	}
	static void longTest() {
		long[] a = new long[max];
		long b = 0,
			 c = 2;
		
		for(int i=0; i<max; i++) {
			a[i] = b;
			b = b + c;
		}
		for(int i=0; i<max; i++) {
			System.out.println(a[i]);
		}
	}
	static void floatTest() {
		float[] a = new float[max];
		float b = 0.0F,
			  c = 2.0F;
		
		for(int i=0; i<max; i++) {
			a[i] = b;
			b = b + c;
		}
		for(int i=0; i<max; i++) {
			System.out.println(a[i]);
		}
	}
	static void doubleTest() {
		double[] a = new double[max];
		double b = 0.0D,
			   c = 2.0D;
		
		for(int i=0; i<max; i++) {
			a[i] = b;
			b = b + c;
		}
		for(int i=0; i<max; i++) {
			System.out.println(a[i]);
		}
	}
	static void shortTest() {
		short[] a = new short[max];
		short b = 0,
			  c = (short)-2000000000;
		
		for(int i=0; i<max; i++) {
			a[i] = b;
			b = (short) (b + c);
		}
		for(int i=0; i<max; i++) {
			System.out.println(a[i]);
		}
	}
	static void byteTest() {
		byte[] a = new byte[max];
		byte b = 0,
			 c = (byte)-2000;
		System.out.println(c);
		for(int i=0; i<max; i++) {
			a[i] = b;
			b = (byte) (b + c);
		}
		for(int i=0; i<max; i++) {
			System.out.println(a[i]);
		}
	}
}
