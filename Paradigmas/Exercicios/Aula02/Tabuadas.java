import java.util.Scanner;

class Tabuadas
{
	public static void main (String args[])
	{
		Scanner teclado = new Scanner (System.in);
		int n;

		System.out.printf ("Digite um número: ");
		n = teclado.nextInt();

		for (int i = 1; i < 10; i++)
			System.out.printf ("%d x %d = %d%n", n, i, n * i);
	}
}
