
public class C2 extends C3 {
	long field_l2;
	int field_i2;
	static int    static_i2;
	//static float  static_f2 = 3.3F;
	//static long   static_l2 = 333L;
	//static double static_d2 = 33.3D;

	static void main(String[] ags) {
		C2 c = new C2();
		c.field_i1 = 9;
		c.field_i2 = c.field_i1;
		//c.metodo0();
	}
	
	void metodo0() {
		C1 c = new C1();
		
		try {
			c.metodo2();
		} catch (E1 e) {
			int i =12;
		}
	}
	
	void metodo1(int i, int j, float f, long l) {
		long l2;
		field_i2 = i;
		field_l2 = l;
		l2 = field_l2;
	}
	void metodo2(int i) {
		if(i<0) {
			i = 10;
		} else {
			i = 100;
		}
		for (int j=0;j<10;j++) {
			i++;
		}
	}
	void metodo3(int i) {
		C2[] a;
		a = new C2[i];
		a[1].field_l2 = 32L;
		a[0].field_l2 = a[1].field_l2;
	}
	void metodo4() {
		double[] ad;
		ad = new double[3];
		ad[2] = 43.0D;
	}
	void metodo5() {
		float[][][] af;
		af = new float[2][2][2];
	}
	void metodo6() {
		C1[][] af;
		af = new C1[2][2];
	}
	void metodo7() {
		field_l2 = 24L;
	}
	
}
