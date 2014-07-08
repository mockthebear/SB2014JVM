class T1 {private int i1;

	public static void main(String[] args) {
            byteTest();
            shortTest();
            intTest();
            floatTest();
            doubleTest();
            intArrayTest();
            intTableTest();
            lookupSwitchTest();
            tableSwitchTest();
            objectTest();
	}
	
	static void intTest() {
		int a = 11;
		int b = -3;
		System.out.println(a+b);
		System.out.println(a-b);
		System.out.println(a*b);
		System.out.println(a/b);
		System.out.println(a%b);
		System.out.println(-a);
		System.out.println();
		System.out.println(a&b);
		System.out.println(a|b);
		System.out.println(a^b);
	}
	static void shortTest() {
		short a = 1111;
		short b = -3;
		System.out.println(a+b);
		System.out.println(a-b);
		System.out.println(a*b);
		System.out.println(a/b);
		System.out.println(a%b);
		System.out.println(-a);
		System.out.println();
		System.out.println(a&b);
		System.out.println(a|b);
		System.out.println(a^b);
	}
	static void byteTest() {
		short a = 18;
		short b = -3;
		System.out.println(a+b);
		System.out.println(a-b);
		System.out.println(a*b);
		System.out.println(a/b);
		System.out.println(a%b);
		System.out.println(-a);
		System.out.println();
		System.out.println(a&b);
		System.out.println(a|b);
		System.out.println(a^b);
	}
	static void longTest() {
		long a = 121L;
		long b = -38L;
		System.out.println(a+b);
		System.out.println(a-b);
		System.out.println(a*b);
		System.out.println(a/b);
		System.out.println(a%b);
		System.out.println(-a);
		System.out.println();
		System.out.println(a&b);
		System.out.println(a|b);
		System.out.println(a^b);
	}
	static void floatTest() {
		float a = 32.45F;
		float b = -4.88F;
		System.out.println(a+b);
		System.out.println(a-b);
		System.out.println(a*b);
		System.out.println(a/b);
		System.out.println(a%b);
		System.out.println(-a);
	}
	static void doubleTest() {
		double a = 3233.405D;
		double b = -42.448D;
		System.out.println(a+b);
		System.out.println(a-b);
		System.out.println(a*b);
		System.out.println(a/b);
		System.out.println(a%b);
		System.out.println(-a);
	}
    static void intArrayTest(){
        int[] array = new int [300];
        for(int i : array){
            array[i] = i;
            System.out.println(array[i]);
        }
    }
    static void intTableTest(){
        int[][] table = new int [100][100];
        int i;
        for(i=0;i<100;i++){
            int j;
            for(j=0;j<100;j++){
                table[i][j] = i*100+j;
                System.out.println(table[i][j]);
            }
        }
    }
    static void lookupSwitchTest(){
        int i =0;
        switch(i){
            case 0:
                
                break;
            case 1:
                i=1;
                break;
            case 100000:
                i=100000;
                break;
            case -100000:
                i=-100000;
                break;
            case -234:
                i=-234;
                break;
            case 39405:
                i=39405;
                break;
            default:
                i=-1;
                break;
        }
        System.out.println(i);
    }
    static void tableSwitchTest(){
        int i =0;
        switch(i){
            case 0:
                
                break;
            case 1:
                i=1;
                break;
            case 2:
                i=2;
                break;
            case 3:
                i=3;
                break;
            case 4:
                i=4;
                break;
            case 5:
                i=5;
                break;
            default:
                i=-1;
                break;
        }
        System.out.println(i);
    }
    static void objectTest(){
        String obj = "primeiro objeto";
        String obj2 = obj;
        obj = "segundo objeto";
        System.out.println("Mesmo objeto?"+obj==obj2+" e mesmo conteúdo"+obj.equals(obj2));
    }
}