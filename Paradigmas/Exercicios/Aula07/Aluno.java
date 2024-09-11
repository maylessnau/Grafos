public class Aluno 
{
	private String nome;
	private String endereco;
	private String email;
	private String telefone;
	private int nota[] = new int[4];

	public void setNome(String nome) 
	{
		this.nome = nome;
	}
	public String getNome() 
	{
		return this.nome;
	}
	public void setEndereco(String endereco) 
	{
		this.endereco = endereco;
	}
	public String getEndereco()
	{
		return this.endereco;
	}
	public void setEmail(String email)
	{
		this.email = email;
	}
	public String getEmail()
	{
		return this.email;
	}
	public void setTelefone(String telefone)
	{
		this.telefone = telefone;
	}			
	public String getTelefone()
	{
		return this.telefone;
	}
	public void setNota (int i, int nota)
	{
		this.nota[i] = nota;
	}
	public int getNota (int i)
	{
		return this.nota[i];
	}
	
	public int calculaMedia()
	{
		int soma;
		soma = 0;

		for (int i = 0; i < 4; i++)
			soma += this.nota[i];

		return (soma/4);
	}
}
