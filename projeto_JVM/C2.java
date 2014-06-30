
public class C2  {
	long field_l2;
	int field_i2 = 21;
	static int    static_i2;
	//static float  static_f2 = 3.3F;
	//static long   static_l2 = 333L;
	//static double static_d2 = 33.3D;

	static void main(String[] ags) {
		C2 c = new C2();
		c.field_i2 = 9;
		//c.field_i2 = c.field_i1;
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
	int metodoi() {
		return 12;
	}
	float metodof() {
		return 12.0F;
	}
	long metodol() {
		return 12L;
	}
	double metodod() {
		return 12.0D;
	}
	C2 metodoa() {
		return new C2();
	}
	
	void metodop() {
		System.out.println("Hello!");
	}
}
