/*
 * Leia as 4 notas de 30 alunos da turma e escreva a maior nota de cada aluno 
 * e a maior nota da turma.
*/

import java.util.Scanner;

class Notas
{
	public static void main (String args[])
	{
		int maiorNota;
		int maiorNotaAluno;
		int nota;

		Scanner teclado = new Scanner (System.in);
		
		maiorNota = 0;
		maiorNotaAluno = 0;
		int i, j;

		for (i = 0; i < 30; i++) 
		{
			for (j = 0; j < 4; j++) 
			{
				nota = teclado.nextInt();
				if (nota > maiorNotaAluno) 
					maiorNotaAluno = nota;
				if (nota > maiorNota)
					maiorNota = nota;
			}
			System.out.printf ("Aluno %d: %d%n", i, maiorNotaAluno);
		}
		System.out.printf ("A maior nota da turma foi: %d%n", maiorNota);
	}
}
