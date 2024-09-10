import java.util.Scanner;

class Triangulos
{
	static public void main (String args[])
	{
		Scanner teclado = new Scanner (System.in);
		int l1, l2, l3;
	
		System.out.printf ("Digite os lados do triângulo: ");
		l1 = teclado.nextInt();
		l2 = teclado.nextInt();
		l3 = teclado.nextInt();

		if (l1 == l2 && l2 == l3)
			System.out.println ("O triângulo é equilátero.");
		else if (l1 == l2 || l1 == l3 || l2 == l3) 
			System.out.println ("O triângulo é isósceles.");
		else
			System.out.println ("O triângulo é escaleno.");
	}
}
