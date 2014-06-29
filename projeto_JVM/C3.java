
public class C3 extends C1{
	static long		static_l2;
	static int		static_i2;
	
	static void main(String[] ags) {
		int i;
		
		i = metodo(3);
	}
	static int metodo(int i) {
		static_i2 = i + 2;
		return static_i2;
	}
	void hello() {
		System.out.println("Hello!");
	}
}
