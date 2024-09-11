import java.util.Scanner;

class Alunos 
{
	public static void main (String args[])
	{
		Scanner teclado = new Scanner(System.in);
		Aluno aluno = new Aluno();

		aluno.setNome (teclado.nextLine());
		aluno.setEndereco (teclado.nextLine());
		aluno.setEmail (teclado.nextLine());
		aluno.setTelefone (teclado.nextLine());
		
		for (int i = 0; i < 4; i++)
			aluno.setNota (teclado.nextInt(), i); 

		System.out.println ("Nome: "+aluno.getNome());
		System.out.println ("Endereco: "+aluno.getEndereco());
		System.out.println ("Email: "+aluno.getEmail());
		System.out.println ("Telefone: "+aluno.getTelefone());

		for (int i = 0; i < 4; i++) 
			System.out.printf("Nota %d: %s%n", i, aluno.getNota(i));
		System.out.println ("Média: " +aluno.calculaMedia()); 
	}
}
