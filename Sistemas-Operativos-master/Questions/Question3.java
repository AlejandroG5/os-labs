package Questions;


public class Question3 {
	
	public int getrandom(int n) {
		int a= (int) (Math.random() *n );
		return a;
	}
	public void getnumber(int numero, int [] a) {
		boolean control=true;
		int n;
		while(control) {
		n=getrandom(numero);
		if(numero==a.length-1) {
			System.out.println("Error de datos introducidos");
		}
		if(lotiene(n, a)) {
			System.out.println("Número no prohibido: "+ n+ " "+ "con una probabilidad de que sea "+n+" del: "+(numero/(numero-(a.length))*10)+"%");
			control=false;
		}	
		}
	}
	public boolean lotiene(int n, int [] a) {
		boolean lotiene=false;
		for(int i=0;i<a.length;i++) {
			if(a[i]!=n && i==a.length-1) {
				lotiene=true;
			}
			else if(a[i]==n) {
				break;
			}
		}
		return lotiene;
	}
	public static void main(String[] args) {
	long start = System.nanoTime();
	Question3 q= new Question3();
	int numero=10;       //AQUI VA N
	int [] a={1,2,3,4,6,7,8,9};   //LISTA PROHIBIDA NO REPETIR NUMERO Y DEBE ESTAR ORDENADA
	q.getnumber(numero,a);
	long finish = System.nanoTime();
	long timeElapsed = finish - start;
	System.out.println("Tiempo: "+timeElapsed +" ns");
	}
}
