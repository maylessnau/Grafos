import java.util.Scanner;

class NumeroPositivo
{
	public static void main (String[] args) 
	{
		int x;	
		Scanner teclado = new Scanner (System.in);

		System.out.printf (" Digite um número inteiro: ");
		x = teclado.nextInt();

		if (x >= 0) 
			System.out.println (" O número é positivo. ");
		else
			System.out.println (" O número não é positivo. ");
	}
} 
