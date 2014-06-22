
public class C1 {
	static int    static_i1;
	static float  static_f1;
	static long   static_l1;
	static double static_d1;
	int    field_i1;
	float  field_f1;
	long   field_l1;
	double field_d1;
	C2 c2;
	
	static void metodo1() {
		static_i1 = 22;
		static_l1 = 2222L;
		static_f1 = 2.2F;
		static_d1 = 22.22D;
	}
	
	void metodo2() {
		field_i1 = 22;
		field_l1 = 2222L;
		field_f1 = 2.2F;
		field_d1 = 22.22D;
	}
	void metodo3() {
		C2 c2;
		c2 = new C2();
	}
	void metodo4() {
		C2.static_i2 = 33;
	}
}
