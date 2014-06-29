
public class C1 {
	int field_i1;
	static long   static_l1 = 333L;
	
	static void main(String[] ags) {
		C2 c = new C2();
		
		c.metodoi();
		c.metodol();
		c.metodof();
		c.metodod();
		c.metodoa();
	}
	
	void metodo1(int i) throws E1 {
		if(i > 0) {
			i = i+10;
		} else {
			throw new E1();
		}
	}
	void metodo2() throws E1 {
		throw new E1();
	}
}
