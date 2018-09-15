package Questions;

import javax.swing.JOptionPane;

public class Question2 {	
	float [] Lista;

	public void Sort (int[] l, int[] r, int[] a) {
		int left=l.length;
		int right=r.length;
		int posicionl=0,posicionr=0,posicionarray=0;
		while(posicionl<left && posicionr<right) {
			if(l[posicionl]<=r[posicionr]) {
				a[posicionarray]=l[posicionl];
				posicionl++;
			}else {
				a[posicionarray]=r[posicionr];
				posicionr++;
			}
			posicionarray++;
		}
		while(posicionl<left){
			a[posicionarray]=l[posicionl];
			posicionl++;
			posicionarray++;
		}
		while(posicionr<right) {
			a[posicionarray]=r[posicionr];
			posicionr++;
			posicionarray++;
		}
	}
	public void MergeSort(int[] a) {
		int largo=a.length;
		int medio=(largo)/2;
		int[] left= new int[medio];
		int[] right=new int[largo-medio];
		if(a.length<2) {
			return;	
		}
		for(int i=0; i<medio;i++) {
			left[i]=a[i];
		}
		for(int j=medio; j<(largo);j++) {
			right[j-medio]=a[j];
		}
		MergeSort(left);
		MergeSort(right);
		Sort(left,right,a);
	}
	public static void main(String[] args) {
		Question2 merch= new Question2();
		int [] a= new int [4];
		int seleccion=0;
		int contador=0;
		float mediana,izq,der;
		while(seleccion!=2) {	
			seleccion = JOptionPane.showOptionDialog(null,"Seleccione opcion", "Selector de opciones",JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,null, new Object[] { "Agregar", "Mediana", "Terminar"},null);
			if (seleccion == 0) {
				if(contador==a.length){
					int [] b= new int [a.length+1];
					for(int i=0;i<a.length;i++) {
						b[i]=a[i];
					}
					a= b;
				}
				a[contador++]= Integer.parseInt(JOptionPane.showInputDialog("Échame el numero"));
			}
			if(seleccion==1) {
				long start = System.nanoTime();
				merch.MergeSort(a);
				for(int i=0;i<a.length;i++) {
					 System.out.print(a[i]+",");
					 System.out.println();
				 }
				if(a.length%2==0) {
					izq=a[a.length/2];
					der=a[(a.length/2-1)];
					mediana=(izq+der)/2;
					System.out.println("La mediana es: "+ mediana);
				}
				else if(a.length%2==1) {
					System.out.println("La mediana es: "+ a[a.length/2]);
				}
				long finish = System.nanoTime();
				long timeElapsed = finish - start;
				System.out.println("Tiempo: "+timeElapsed +" ns");
			}
		}
		
	}
}