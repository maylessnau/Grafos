import java.util.Scanner;

class ParOuImpar 
{
	public static void main (String args[]) 
	{
		int n;
		Scanner teclado = new Scanner (System.in);

		System.out.printf (" Digite um número: ");
		n = teclado.nextInt();

		if ((n%2) == 0) 
			System.out.println (" O número é par.");
		else
			System.out.println (" O número é ímpar.");
	}
}
