import java.util.Scanner;

class Sorteio 
{
	static public void main (String args[])
	{
		Scanner teclado = new Scanner(System.in);
		String nomes[] = new String[5];

		for (int i = 0; i < 5; i++) 
		{
			System.out.printf ("Entre com o %d nome: ", i);
			nomes[i] = teclado.nextLine();
		}

		int sorteio = (int)(Math.random()*5);

		System.out.println ("O vencedor é "+nomes[sorteio]);
	}
}
