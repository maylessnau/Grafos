import java.util.Scanner;

class Idades 
{
	static public void main (String args[])
	{
		Scanner teclado = new Scanner (System.in);
		int idades[] = new int[10];
		double media;

		System.out.println ("Digite as idades: ");

		media = 0;
		for (int i = 0; i < 10; i++) 
		{
			idades[i] = teclado.nextInt();
			/* Media por enquanto guarda a soma das idades */
			media += idades[i];
		}
		/* Agora calculamos a media mesmo (media(soma)/10) */
		media /= 10;
		System.out.println ("A média das idades é "+media);
		
		for (int i = 0; i < 10; i++)
		{ 
			if (idades[i] > media) 
				System.out.printf ("%d está acima da média%n", idades[i]);
			else 
				System.out.printf ("%d está abaixo da média%n", idades[i]);
		}
		teclado.close();
	}					
}
