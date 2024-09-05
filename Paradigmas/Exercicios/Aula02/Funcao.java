import java.util.Scanner;

/*
* Leia um número x, calcule e escreva o valor da função f(x), dada por:
* 0 <= x < 5;     f(x) = x
* 5 <= x < 10;    f(x) = 2x+1
* x >= 10;        f(x) = x-3 
*/

class Funcao
{
	public static void main (String args[])
	{
		int x;
		Scanner teclado = new Scanner(System.in);

		System.out.printf (" Digite o valor de x: ");
		x = teclado.nextInt();

		if (x >= 0 && x < 5) 
			System.out.println (" O valor de f(x) é " + x);
		else if (x >= 5 && x < 10) 
			System.out.println (" O valor de f(x) é " + (2 * x + 1));
		else if (x >= 10)
			System.out.println (" O valor de f(x) é " + (x - 3));
		else
			System.out.println (" Esse valor de x não pertence ao domínio da função");
	}
}
