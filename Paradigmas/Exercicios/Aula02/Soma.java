import java.util.Scanner;

class Soma
{
	public static void main (String args[]) 
	{
		Scanner teclado = new Scanner (System.in);
		int n;
		int soma;
		
		System.out.printf ("Digite os números: ");
		n = teclado.nextInt();

		soma = 0;
		while (n != -1) 
		{
			soma += n;
			n = teclado.nextInt();
		}

		System.out.printf ("A soma é %d.%n", soma);
	}
}
