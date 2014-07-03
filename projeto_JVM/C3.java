
public class C3{
	static long		static_l2;
	static int		static_i2;
	
	static public void main(String[] ags) {
		C3 c = new C3();
		c.metodo33();
	}
	static int metodo(int i) {
		static_i2 = i + 2;
		return static_i2;
	}
	void hello() {
		System.out.println("Hello!");
	}
	void metodo31() {	
		C2[][] ca = new C2[2][3];
		for(int i=0;i<2; i++) {
			ca[i] = new C2[3];
			for(int j=0;j<3; j++)
				ca[i][j] = new C2();
		}
	}
	void metodo32() {	
		C2[] ca = new C2[2];
		ca[0].metodo0();
	}
	void metodo33() {	
		int[] array = new int[10];
		for(int i=0;i<10; i++) {
			array[i] = 5+i;
		}
		metodo34(array);
	}
	void metodo34(int[] array) {
		int t = 0;
		for(int i=0;i<10; i++) {
			t = t + array[i];
			System.out.println(t);
		}
	}
}
