class t4 {
	static final int imax = 3;
	static final int jmax = 4;
	public static void main(String[] args) {
		doubleTest();
	}
	
	static void intTest() {
		int[][] a = new int[imax][jmax];
		int b = 0,
			c = 2;
		
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++) {
				a[i][j] = b;
				b = b + c;
			}
		}
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++)
				System.out.println(a[i][j]);
		}
	}
	static void longTest() {
		long[][] a = new long[imax][jmax];
		long b = 0,
			 c = 2;
		
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++) {
				a[i][j] = b;
				b = b + c;
			}
		}
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++)
				System.out.println(a[i][j]);
		}
	}
	static void floatTest() {
		float[][] a = new float[imax][jmax];
		float b = 0.0F,
			  c = 2.0F;
		
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++) {
				a[i][j] = b;
				b = b + c;
			}
		}
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++)
				System.out.println(a[i][j]);
		}
	}
	static void doubleTest() {
		double[][] a = new double[imax][jmax];
		double b = 0.0D,
			   c = 2.0D;
		
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++) {
				a[i][j] = b;
				b = b + c;
			}
		}
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++)
				System.out.println(a[i][j]);
		}
	}
	static void shortTest() {
		short[][] a = new short[imax][jmax];
		short b = 0,
			  c = (short)-2000000500;
		
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++) {
				a[i][j] = b;
				b = (short)(b + c);
			}
		}
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++)
				System.out.println(a[i][j]);
		}
	}
	static void byteTest() {
		byte[][] a = new byte[imax][jmax];
		byte b = 0,
			 c = (byte)-2000004400;
		
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++) {
				a[i][j] = b;
				b = (byte)(b + c);
			}
		}
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++)
				System.out.println(a[i][j]);
		}
		System.out.println("Hello!");
	}
	void teste() {
		int i = 555555555;
		long l = 55;
		float f = 55.0F;
		double d = 55.0D;
	}
}
