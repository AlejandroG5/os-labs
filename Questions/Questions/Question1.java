package Questions;
public class Question1 {
	public String palabra(String a) {
		for (int i = 0; i < a.length(); i++) {
			for(int j=0;j<a.length();j++) {
				if((a.charAt(i)==a.charAt(j))&&(i!=j)) {
					break;
				}
				else if ((a.charAt(i)!=a.charAt(j))&&(j==a.length()-1)){
					return "Esta es: "+a.charAt(i);
				}
			}
		}
		return "Todas repetidas";
	}
public static void main(String[] args) {
	long start = System.nanoTime();
	Question1 prueba= new Question1();
	System.out.println(prueba.palabra("google"));
	// ...
	long finish = System.nanoTime();
	long timeElapsed = finish - start;
	System.out.println("Tiempo: "+timeElapsed +" ns");
}
}