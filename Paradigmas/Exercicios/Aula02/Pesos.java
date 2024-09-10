/*
 * Fazer um programa que leia os valores do peso e da altura de pessoas, enquanto 
 * não for digitado o número -1, conte e escreva quantas pessoas estão acima do 
 * peso. A condição (peso /(altura*altura)) <= 25 diz que a pessoa está no peso 
 * normal.
*/

import java.util.Scanner;

class Pesos 
{
	public static void main (String args[])
	{
		Scanner teclado = new Scanner (System.in);
		double peso, altura;
		int acimaPeso;

		System.out.printf ("Digite o peso e a altura, respectivamente: ");
		peso = teclado.nextDouble();
		altura = teclado.nextDouble();
		acimaPeso = 0;

		while (peso != -1 || altura != -1)
		{
			if ((peso / (altura * altura)) > 25) 
			{ 
				acimaPeso += 1;	
			}
			System.out.printf ("Digite o peso e a altura, respectivamente: ");
			peso = teclado.nextDouble();
			altura = teclado.nextDouble();
		}
		System.out.printf ("%d pessoas estão acima do peso.%n", acimaPeso);
	}
}
