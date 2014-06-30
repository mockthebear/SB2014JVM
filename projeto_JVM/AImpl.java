
public class AImpl implements A{
       public void a(long l)
    {
       System.out.println("Do something");
    }
    public static void main(String[] args){
      A aa;
	  AImpl aaa = new AImpl();
	  aa = aaa;
	  aaa.a(1L);
	  aa.a(1L);
    }

}
