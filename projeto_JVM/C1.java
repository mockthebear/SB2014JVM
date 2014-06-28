
public class C1 {
	int field_i1;
	static long   static_l1 = 333L;
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
