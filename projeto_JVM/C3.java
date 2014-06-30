
public class C3{
	static long		static_l2;
	static int		static_i2;
	
	static public void main(String[] ags) {
		float f;
		
		f = 3/0;
		C3 c = new C3();
		c.metodo32();
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
}
